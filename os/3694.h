#ifndef _3694_H_INCLUDED_
#define _3694_H_INCLUDED_

struct h8_3694f_tmra 
{
  volatile uint8 tma;
  volatile uint8 tca;
};

struct h8_3694f_sci {
  volatile uint8 smr;
  volatile uint8 brr;
  volatile uint8 scr3;
  volatile uint8 tdr;
  volatile uint8 ssr;
  volatile uint8 rdr;
};

#define H8_3694F_SCI3 ((volatile struct h8_3694f_sci *)0xffa8)
#define H8_3694F_TMRA ((volatile struct h8_3694f_tmra *)0xffa6)
#define H8_3694F_IRR1 ((volatile uint8 *)0xfff6)
#define PCR8 ((volatile uint8 *)0xffeb)
#define PDR8 ((volatile uint8 *)0xffdb)
#define PDRB ((volatile uint8 *)0xffdd)
#define ADDRA ((volatile uint16 *)0xffb0)
#define ADCSR ((volatile uint8 *)0xffb8)
#define PMR1 ((volatile unsigned char *)0xffe0)
#define MSTCR1 ((volatile unsigned char *)0xfff9)

#define H8_3694F_TMRA_TMA_500MSEC (1<<0)
#define H8_3694F_TMRA_TMA_TMA2 (1<<2)
#define H8_3694F_TMRA_TMA_CLR (3<<2)
#define H8_3694F_IRR1_IRRTA (1<<6)

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
#define H8_3694F_SCI_SCR3_RE     (1<<4) /* ¼õ¿®Í­¸ú */
#define H8_3694F_SCI_SCR3_TE     (1<<5) /* Á÷¿®Í­¸ú */
#define H8_3694F_SCI_SCR3_RIE    (1<<6) /* ¼õ¿®³ä¹þ¤ßÍ­¸ú */
#define H8_3694F_SCI_SCR3_TIE    (1<<7) /* Á÷¿®³ä¹þ¤ßÍ­¸ú */

#define H8_3694F_SCI_SSR_MPBT   (1<<0)
#define H8_3694F_SCI_SSR_MPB    (1<<1)
#define H8_3694F_SCI_SSR_TEND   (1<<2)
#define H8_3694F_SCI_SSR_PER    (1<<3)
#define H8_3694F_SCI_SSR_FERERS (1<<4)
#define H8_3694F_SCI_SSR_ORER   (1<<5)
#define H8_3694F_SCI_SSR_RDRF   (1<<6) /* ¼õ¿®´°Î» */
#define H8_3694F_SCI_SSR_TDRE   (1<<7) /* Á÷¿®´°Î» */

#define TXD (1<<1)

#define MSTS3 (1<<5)

#define ADST (1<<5)
#define ADF  (1<<7)

#endif
