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
	mov rdx, r14 ; rdx = current.x
	mov rcx, r15 ; rcx  = current.y
	sub rdx, r12 ; rdx = current.x-click.x
	sub rcx, r13 ; rcx = current.y-click.y
	mov rax, rdx ; rax = current.x-click.x
	mul eax ; rax = (current.x-click.x)^2
	mov rdx, rax ; rdx = (current.x-click.x)^2
	mov rax, rcx ;	rax = (current.y-click.y)
	mul eax ; rax = (current.y-click.y)^2
	mov rcx, rax ; rcx = (current.y-click.y)^2
	add rcx, rdx ;  rcx = (current.x-click.x)^2 + (current.y-click.y)^2
	xor rsi, rsi
	xor rdi, rdi
	mov sil, [r10] ; load to eax pixel from output1
	mov dil, [r11] ; load to ebx pixel from output2
	push rcx ; push (current.x-click.x)^2+(current.y-click.y)^2 on stack
	fild qword [rsp] ; put rcx to ST(0)
	pop rcx ; poping to restore rsp
	fsqrt ; sqrt of rcx ((current.x-click.x)^2 + (current.y-click.y)^2) 
	fldpi ; st1 = pi
	fdiv ; divided by pi
	sub rsp, 4
	fstp dword [rsp]
	add rsp, 4
	
	push qword 2
	fild qword [rsp]
	add rsp, 8
	fdiv ; division by 2
	sub rsp, 8
	fstp qword [rsp]
	add rsp, 8
	push qword 10 ; PEROID
	fild qword [rsp] ; put PEROID to ST(1)
	add rsp, 8
	fmul ; c = sqrt(current.x-click.x)^2 + (current.y-click.y)^2)/2pi*PEROID
	fprem ; c%PEROID
	sub rsp, 8
	fstp qword [rsp]
	add rsp, 8
	fsin ; calculate sin of reminder
	fabs ; absolute value
	
	push rsi
	fild qword [rsp]
	fmul
	fistp qword [rsp]
	pop rsi
	
	mov [r10], sil
	sub dil, sil
	
	sub rsp, 8
	fstp qword [rsp]
	add rsp, 8	

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
