	.h8300hn
	.section .text
	.global	_start
	.type	_start,@function
_start:
	mov.w	#_stack,sp
	jsr	@_main

1:
	bra	1b
