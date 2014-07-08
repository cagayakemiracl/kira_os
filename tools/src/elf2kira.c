#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <elf.h>

#define SIZE 1024 * 3 // h8 3694f ram 2kb
#define INPUT "kiraos"
#define OUTPUT "kiraos.kira"

static int elf_check(const Elf32_Ehdr *header)
{
  const int machine = ntohs(header->e_machine);
  
  if (memcmp((void *) header, ELFMAG, SELFMAG))          return -1; // ELF file
  if (header->e_ident[EI_CLASS]   != ELFCLASS32)         return -1; /* ELF32 */
  if (header->e_ident[EI_DATA]    != ELFDATA2MSB)        return -1; /* Big endian */
  if (header->e_ident[EI_VERSION] != EV_CURRENT)         return -1; /* Version 1 */
  if (ntohs(header->e_type)       != ET_EXEC)            return -1; /* Executable file */
  if (ntohl(header->e_version)    != EV_CURRENT)         return -1; /* Version 1 */
  if ((machine != EM_H8_300) && (machine != EM_H8_300H)) return -1; /* Hitachi H8/300 of H8/300 */

  return 0;
}
/*
static int elf_extract_program(const Elf32_Ehdr *header, const FILE *row_file)
{
  const char d = 0;
  int i;
  Elf32_Phdr *phdr;
  
  for (i = 0; i < ntohs(header->e_phnum); i++) {
    phdr = (Elf32_Phdr *) ((char *)header + ntohl(header->e_phoff) + ntohs(header->e_phentsize) * i);
    if (ntohl(phdr->p_type) != PT_LOAD)
      continue;

    printf("%d\n%d\n", ntohl(phdr->p_offset), ntohl(phdr->p_filesz));
    fwrite((char *)header + ntohl(phdr->p_offset), sizeof(char), ntohl(phdr->p_filesz), (FILE *) row_file);
    fwrite(&d, sizeof(char), ntohl(phdr->p_memsz) - ntohl(phdr->p_filesz), (FILE *) row_file);
  }

  return 0;
}
*/
static int elf_extract_program(const Elf32_Ehdr *header, const FILE *row_file)
{
  const char d = 0;
  int i, type;
  Elf32_Shdr *shdr;
  
  for (i = 0; i < ntohs(header->e_shnum); i++) {
    shdr = (Elf32_Shdr *) ((char *)header + ntohl(header->e_shoff) + ntohs(header->e_shentsize) * i);
    type = ntohl(shdr->sh_type);
    
    if (type == SHT_NULL) {
      puts("type NULL");
      continue;
    } else if (type == SHT_PROGBITS) {
      puts("type PROGBITS");
      fwrite((char *)header + ntohl(shdr->sh_offset), sizeof(char), ntohl(shdr->sh_size), (FILE *) row_file);
    } else if (type == SHT_NOBITS) {
      puts("type NOBITS");
      fwrite(&d, sizeof(char), ntohl(shdr->sh_size), (FILE *) row_file);
      
      return 0;
    }
  }

  return 0;
}

static int kira_write(const char *input, const char *output)
{
  const Elf32_Ehdr *header = (const Elf32_Ehdr *) malloc(SIZE);
  const FILE *elf_file = fopen(input, "rb");
  const FILE *row_file = fopen(output, "wb");
  
  fread((void *) header, sizeof(char), SIZE, (FILE *) elf_file);
  if (elf_check(header) < 0)
    return -1;

  puts("check clear");
  if (elf_extract_program(header, row_file) < 0)
    return -1;

  puts("complete");
  fclose((FILE *) elf_file);
  fclose((FILE *) row_file);
  
  return 0;
}

int main(int argc, char **argv)
{
  char *input, *output;

  if (argc == 3) {
    input = argv[1];
    output = argv[2];
  } else {
    input = INPUT;
    output = OUTPUT;
  }

  printf("%s\n%s\n", input, output);
  
  return kira_write((const char *) input, (const char *) output);
}
