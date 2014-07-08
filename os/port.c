#include "defines.h"
#include "3694.h"
#include "port.h"

static volatile uint8 *port8_con = PCR8;
static volatile uint8 *port8_data = PDR8;
static volatile uint8 *portb_data = PDRB;
static volatile uint8 *ad_con = ADCSR;

static void port8_init(uint8 set)
{
  *port8_con = set;
}

/*
void port8_input(void)
{
  port8_init(0x00);
}
*/
void port8_output(void)
{
  port8_init(0xff);
}

void port8_write(uint8 data)
{
  *port8_data = data;
}

uint8 port8_read(void)
{
  return *port8_data;
}

uint8 portb_read(void)
{
  uint8 a, b;
  uint8 tmp = *ad_con;
  
  *ad_con = 7;
  a = *portb_data;
  
  *ad_con = 0;
  b = *portb_data;
  *ad_con = tmp;

  return a | b;
}
