#include "defines.h"
#include "serial.h"

#define H8_3694F_SCI3 ((volatile struct h8_3694f_sci *)0xffa8)

struct h8_3694f_sci {
  volatile uint8 smr;
  volatile uint8 brr;
  volatile uint8 scr3;
  volatile uint8 tdr;
  volatile uint8 ssr;
  volatile uint8 rdr;
};

#define H8_3694F_SCI_SMR_CKS_PER1  (0<<0)
#define H8_3694F_SCI_SMR_CKS_PER4  (1<<0)
#define H8_3694F_SCI_SMR_CKS_PER16 (2<<0)
#define H8_3694F_SCI_SMR_CKS_PER64 (3<<0)
#define H8_3694F_SCI_SMR_MP     (1<<2)
#define H8_3694F_SCI_SMR_STOP   (1<<3)
#define H8_3694F_SCI_SMR_OE     (1<<4)
#define H8_3694F_SCI_SMR_PE     (1<<5)
#define H8_3694F_SCI_SMR_CHR    (1<<6)
#define H8_3694F_SCI_SMR_CA     (1<<7)

#define H8_3694F_SCI_SCR3_CKE0   (1<<0)
#define H8_3694F_SCI_SCR3_CKE1   (1<<1)
#define H8_3694F_SCI_SCR3_TEIE   (1<<2)
#define H8_3694F_SCI_SCR3_MPIE   (1<<3)
#define H8_3694F_SCI_SCR3_RE     (1<<4) /* 受信有効 */
#define H8_3694F_SCI_SCR3_TE     (1<<5) /* 送信有効 */
#define H8_3694F_SCI_SCR3_RIE    (1<<6) /* 受信割込み有効 */
#define H8_3694F_SCI_SCR3_TIE    (1<<7) /* 送信割込み有効 */

#define H8_3694F_SCI_SSR_MPBT   (1<<0)
#define H8_3694F_SCI_SSR_MPB    (1<<1)
#define H8_3694F_SCI_SSR_TEND   (1<<2)
#define H8_3694F_SCI_SSR_PER    (1<<3)
#define H8_3694F_SCI_SSR_FERERS (1<<4)
#define H8_3694F_SCI_SSR_ORER   (1<<5)
#define H8_3694F_SCI_SSR_RDRF   (1<<6) /* 受信完了 */
#define H8_3694F_SCI_SSR_TDRE   (1<<7) /* 送信完了 */

#define PMR1 ((volatile unsigned char *)0xffe0)
#define TXD (1<<1)

#define MSTCR1 ((volatile unsigned char *)0xfff9)
#define MSTS3 (1<<5)

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

int serial_is_send_enable(void)
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

int serial_is_recv_enable(void)
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
