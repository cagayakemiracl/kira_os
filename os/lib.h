#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

void *memset(void *b, int c, int len);
void *memcpy(void *dst, const void *src, int len);
//int memcmp(const void *b1, const void *b2, int len);
//int strlen(const char *s);
//char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, int len);

//int putc(char c);    /* ��ʸ������ */
//char getc(void);     /* ��ʸ������ */
int puts(char *str); /* ʸ�������� */
int gets(char *buf); /* ʸ�������� */
int putxval(unsigned int value, int column); /* ���ͤ�16��ɽ�� */
int atoi(char *str);

#endif
