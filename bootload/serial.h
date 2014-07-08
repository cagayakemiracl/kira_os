#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

int serial_init(void);
int serial_is_send_enable(void);
int serial_send_byte(char b);
int serial_is_recv_enable(void);
char serial_recv_byte(void);

#endif
