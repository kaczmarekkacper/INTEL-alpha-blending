section .text

	global f

f:
	; r8 - width1
	; r9 - height1
	; r10 - pointer on first element in output1 array
	; r11 - pointer on first element in output2 array
	; r12 - click.x
	; r13 - click.y
	; r14 - current x
	; r15 - current y
	mov r10, rdi
	add r10, 121 ; set output1 in begin position of pixel array - 4
	mov r11, rsi
	add r11, 121 ; set output2 in begin position of pixel array - 4
	mov r12, rdx ; move mouse's x position
	mov r13, rcx ; move mouse's y position
	mov r14, 1 ; x value of current pixel
	mov r15, 1 ; y value of current pixel
	
loop:
	add r10, 4
	add r11, 4
	
	
	push r14
	fild qword [rsp]
	pop r14
	push r12
	fild qword [rsp]
	pop r12
	fsubp
	fmul st0, st0
	push r15
	fild qword [rsp]
	pop r15
	push r13
	fild qword [rsp]
	pop r13
	fsubp
	fmul st0, st0
	faddp

	fsqrt ; sqrt of rcx ((current.x-click.x)^2 + (current.y-click.y)^2) 
	fsin ; calculate sin of reminder
	fabs ; absolute value
	
	xor rsi, rsi
	xor rdi, rdi
	mov sil, [r10] ; load to eax pixel from output1
	mov dil, [r11] ; load to ebx pixel from output2
	
	push rsi
	fild qword [rsp] ; content of register is st0, abs(sin) is st1
	fmulp
	fistp qword [rsp]
	pop rsi
	
	mov [r10], sil
	sub dil, sil	

	mov [r11], dil
	cmp r8, r14
	jne incX
	cmp r9, r15
	jne incY
	ret

incX:
	inc r14
	jmp loop
incY:
	inc r15
	xor r14, r14
	add r14, 1
	jmp loop
