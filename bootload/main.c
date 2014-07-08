#include "defines.h"
#include "serial.h"
#include "xmodem.h"
#include "lib.h"

static int init(void)
{
  extern int erodata, data_start, edata, bss_start, ebss;

  memcpy(&data_start, &erodata, &edata - &data_start);
  memset(&bss_start, 0, &ebss - &bss_start);
  serial_init();
  
  return 0;
}

static void wait()
{
  volatile long i;
  for (i = 0; i < 300000; i++)
    ;
}

int main(void)
{
  static int size = -1;
  static char *loadbuf = NULL;
  static char buf[16];
  void (*f)(void);
  extern int buffer_start;
  
  init();

  puts("kira load (kira os boot loader) started.\n");
  
  while (1) {
    puts("kira load> ");
    gets(buf);

    if (!strcmp(buf, "load")) {
      loadbuf = (char *)(&buffer_start);
      size = xmodem_recv(loadbuf);
      wait();
      if (size < 0) {
        puts("\nXMODEM receive error!\n");
      }
      else {
        puts("\nXMODEM receive succeeded.\n");
      }
      puts("starting from buffer start: ");
      putxval((unsigned int)loadbuf, 0);
      puts("\n");
      f = (void (*)(void))loadbuf;
      f();
    } else if (!strncmp(buf, "echo", 4)) {
      puts(buf + 4);
      puts("\n");
    } else if (!strcmp(buf, "help")) {
      puts("echo\nload\n");
    } else {
      puts("unknown.\n");
    }
  }
  
  return 0;
}
