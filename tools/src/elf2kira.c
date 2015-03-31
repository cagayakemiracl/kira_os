#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <elf.h>

#define SIZE 1024 * 3  // h8 3694f ram 2kb
#define INPUT "kiraos"
#define OUTPUT "kiraos.kira"

static int elf_check(const Elf32_Ehdr *header) {
  const int machine = ntohs(header->e_machine);

  if (memcmp((void *)header, ELFMAG, SELFMAG)) return -1;    // ELF file
  if (header->e_ident[EI_CLASS] != ELFCLASS32) return -1;    // ELF32
  if (header->e_ident[EI_DATA] != ELFDATA2MSB) return -1;    // Big endian
  if (header->e_ident[EI_VERSION] != EV_CURRENT) return -1;  // Version 1
  if (ntohs(header->e_type) != ET_EXEC) return -1;           // Executable file
  if (ntohl(header->e_version) != EV_CURRENT) return -1;     // Version 1
  if ((machine != EM_H8_300) && (machine != EM_H8_300H))
    return -1;  // Hitachi H8/300 of H8/300

  return 0;
}

static int elf_extract_program(const Elf32_Ehdr *header, const FILE *row_file) {
  const char d = 0;
  int i;

  for (i = 0; i < ntohs(header->e_shnum); i++) {
    Elf32_Shdr *shdr = (Elf32_Shdr *)((char *)header + ntohl(header->e_shoff) +
                                      ntohs(header->e_shentsize) * i);
    int type = ntohl(shdr->sh_type);

    switch (type) {
      case SHT_NULL:
        puts("type NULL");
        break;
      case SHT_PROGBITS:
        puts("type PROGBITS");
        fwrite((char *)header + ntohl(shdr->sh_offset), sizeof(char),
               ntohl(shdr->sh_size), (FILE *)row_file);
        break;
      case SHT_NOBITS:
        puts("type NOBITS");
        fwrite(&d, sizeof(char), ntohl(shdr->sh_size), (FILE *)row_file);
        return 0;  // because the executable file ending in bss area
      default:
        return -1;  // not to file in the above type is abnormal
    }
  }

  return -1;  // bss area does not exist file is abnormal
}

static void finalize_kira_write(const Elf32_Ehdr *header, const FILE *elf_file,
                                const FILE *row_file) {
  free((void *)header);
  fclose((FILE *)elf_file);
  fclose((FILE *)row_file);
}

static int kira_write(const char *input, const char *output) {
  const Elf32_Ehdr *header = (const Elf32_Ehdr *)malloc(SIZE);
  const FILE *elf_file = fopen(input, "rb");
  const FILE *row_file = fopen(output, "wb");

  fread((void *)header, sizeof(char), SIZE, (FILE *)elf_file);
  if (elf_check(header) < 0) {
    finalize_kira_write(header, elf_file, row_file);
    return -1;
  }

  puts("check clear");
  if (elf_extract_program(header, row_file) < 0) {
    finalize_kira_write(header, elf_file, row_file);
    return -1;
  }

  puts("complete");
  finalize_kira_write(header, elf_file, row_file);

  return 0;
}

int main(int argc, char **argv) {
  char *input, *output;

  if (argc == 3) {
    input = argv[1];
    output = argv[2];
  } else {
    input = INPUT;
    output = OUTPUT;
  }

  printf("%s\n%s\n", input, output);

  return kira_write((const char *)input, (const char *)output);
}
