#include "defines.h"
#include "3694.h"
#include "serial.h"

static volatile struct h8_3694f_sci *sci = H8_3694F_SCI3;

/* �ǥХ�������� */
int serial_init(void)
{
  *MSTCR1 &= ~MSTS3;
  *PMR1 |= TXD;
   
  sci->scr3 = 0;
  sci->smr = 0;
  sci->brr = 64; /* 20MHz�Υ���å�����9600bps������(25MHz�ξ���80�ˤ���) */
  sci->scr3 = H8_3694F_SCI_SCR3_RE | H8_3694F_SCI_SCR3_TE; /* ��������ǽ */
  sci->ssr = 0;

  return 0;
}

static int serial_is_send_enable(void)
{
  return (sci->ssr & H8_3694F_SCI_SSR_TDRE);
}

int serial_send_byte(char c)
{
  while (!serial_is_send_enable())
    ;
  sci->tdr = (unsigned char) c;
//  sci->ssr &= ~H8_3694F_SCI_SSR_TDRE; /* �������� */

  return 0;
}

static int serial_is_recv_enable(void)
{
  return (sci->ssr & H8_3694F_SCI_SSR_RDRF);
}

char serial_recv_byte(void)
{
  char c;

  while (!serial_is_recv_enable())
    ;
  c = (char) sci->rdr;
  //sci->ssr &= ~H8_3694F_SCI_SSR_RDRF; /* ������λ */

  return c;
}
