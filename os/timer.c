#include "defines.h"
#include "3694.h"
#include "timer.h"

static volatile struct h8_3694f_tmra *tmra = H8_3694F_TMRA;
static volatile uint8 *irr1 = H8_3694F_IRR1;

static void timer_clear(void)
{
  tmra->tma |= H8_3694F_TMRA_TMA_CLR;
  *irr1 &= ~H8_3694F_IRR1_IRRTA;
}

void timer_init(void)
{
  timer_clear();
  tmra->tma |= H8_3694F_TMRA_TMA_500MSEC;
}

static void timer_start(void)
{
  tmra->tma &= ~H8_3694F_TMRA_TMA_TMA2;
}

static int timer_is_expired(void)
{
  return (*irr1 & H8_3694F_IRR1_IRRTA) ? 1 : 0;
}

void timer_wait(void)
{
  timer_start();
  while (!timer_is_expired())
    ;
  timer_clear();
}

void timer_01(void)
{
  volatile int i;

  for (i = 0; i < 275; ++i)
    ;
}
