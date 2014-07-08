#include "defines.h"
#include "3694.h"
#include "serial.h"

static volatile struct h8_3694f_sci *sci = H8_3694F_SCI3;

/* デバイス初期化 */
int serial_init(void)
{
  *MSTCR1 &= ~MSTS3;
  *PMR1 |= TXD;
   
  sci->scr3 = 0;
  sci->smr = 0;
  sci->brr = 64; /* 20MHzのクロックから9600bpsを生成(25MHzの場合は80にする) */
  sci->scr3 = H8_3694F_SCI_SCR3_RE | H8_3694F_SCI_SCR3_TE; /* 送受信可能 */
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
//  sci->ssr &= ~H8_3694F_SCI_SSR_TDRE; /* 送信開始 */

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
  //sci->ssr &= ~H8_3694F_SCI_SSR_RDRF; /* 受信完了 */

  return c;
}
