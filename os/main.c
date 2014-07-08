#include "defines.h"
#include "port.h"
#include "serial.h"
#include "timer.h"
#include "ad.h"
#include "lib.h"

static uint8 table[30] = { 127,153,178,201,221,236,247,253,253,247,236,221,201,178,153,127,100,75,52,32,17,6,0,0,6,17,32,52,75,100, };

static int init(void)
{
  serial_init();
  port8_output();
  timer_init();
  ad_init();
  
  return 0;
}

static void nokogiri(void)
{
  int num;
  
  while (1) {
    timer_01();
    num = port8_read();
    port8_write(num + 1);
  }
}

static void adsin(void)
{
  int i;
  
  for (i = 0; i < 30; ++i) {
    timer_01();
    port8_write((uint8) table[i]);
    ad_print();
  }
}

static void dasin(void)
{
  int i;

  while (1) {
    for (i = 0; i < 30; ++i) {
      timer_01();
      port8_write((uint8) table[i]);
    }
  }
}

int main(void)
{
  static char buf[16];
  int num;

  init();

  puts("\nkira os boot successd!.\n");
  
  while (1) {
    puts("kira OS> ");
    gets(buf);

    if (!strncmp(buf, "echo", 4)) {
      puts(buf + 4);
      puts("\n");
    } else if (!strcmp(buf, "read")) {
      puts("port8: ");
      putxval((unsigned int) port8_read(), 0);
      puts("\n");
    } else if (!strncmp(buf, "write", 5)) {
      num = atoi(buf + 6);
      port8_write((uint8) num);
    } else if (!strcmp(buf, "nokogiri")) {
      nokogiri();
    } else if (!strcmp(buf, "ad")) {
      ad_print();
    } else if (!strcmp(buf, "adsin")) {
      adsin();
    } else if (!strcmp(buf, "dasin")) {
      dasin();
    } else if (!strcmp(buf, "help")) {
      puts("echo\nread\nwrite\nnokogiri\nad\nhelp\nadsin\ndasin\n");
    } else {
      puts("unknown.\n");
    }
  }

  return 0;
}
