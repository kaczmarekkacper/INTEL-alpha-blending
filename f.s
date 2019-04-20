section .data
	OFFSET	equ	54
	PEROID: dw 6.2831
	TWOPI: dw 6.2831
section .bss
	c: resq 1
	
extern sin

section .text

	global f

f:
	; r8 
	mov r10, rdi
	add r10, OFFSET ; set output1 in begin position of pixel array 
	mov r11, rsi
	add r11, OFFSET ; set output2 in begin position of pixel array
	mov r12, rdx ; move mouse's x position
	mov r13, rcx ; move mouse's y position
	mov r14, 0 ; x value of current pixel
	mov r15, 0 ; y value of current pixel
	
loop:
	mov rdx, r14
	mov rcx, r15
	
	sub rdx, r8 ; width-click.x
	sub rcx, r9 ; height-click.y
	mov rax, rdx ; rax = width-click.x
	mul eax ; (width-click.x)^2
	mov rdx, rax ; rdx = (width-click.x)^2
	mov rax, rcx ;	rax = (height-click.y)
	mul eax ; rax = (height-click.y)^2
	mov rcx, rax ; rcx = (height-click.y)^2
	add rcx, rdx ;  rcx = (width-click.x)^2 + (height-click.y)^2
	
	fild rcx ; put rcx to ST(0)
	fsqrt ; sqrt of rcx (c)
	fmul TWOPI ; create new peroid
	fild PEROID ; put PEROID to ST(1)
	fprem ; dision with reminder c*2pi%PEROID
	faddp 0x0 ; pop ST(1)
	fsin ; calculate sin of reminder
	fabs ; absolute value
	fmul 
	fstp c
	
	
	
	ret
