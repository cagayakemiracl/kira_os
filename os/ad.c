#include "defines.h"
#include "3694.h"
#include "ad.h"
#include "lib.h"

static volatile uint8 *adcsr = ADCSR;
static volatile uint16 *addra = ADDRA;

static int ad_is_end(void)
{
  return (*adcsr & ADF);
}

static void ad_start(void)
{
  *adcsr |= ADST;
}

static void ad_end_clear(void)
{
  *adcsr &= ~ADF;
}

void ad_init(void)
{
  *adcsr = 4;
}

uint16 ad_result(void)
{
  uint16 ret;

  ad_start();
  while (!ad_is_end())
    ;

  ret = *addra;
  ad_end_clear();
  ret >>= 6;
  
  return ret;
}

uint16 ad_print(void)
{
  uint16 ret;

  ret = ad_result();
  putxval((unsigned int) ret, 0);
  puts("\n");
  
  return ret;
}

  
