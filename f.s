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
	imul eax ; rax = (current.x-click.x)^2
	mov rdx, rax ; rdx = (current.x-click.x)^2
	mov rax, rcx ;	rax = (current.y-click.y)
	imul eax ; rax = (current.y-click.y)^2
	mov rcx, rax ; rcx = (current.y-click.y)^2
	add rcx, rdx ;  rcx = (current.x-click.x)^2 + (current.y-click.y)^2
	
	push word 20 ; PEROID
	fild word [rsp]; st0 = PEROID
	add rsp, 2
	push rcx ; push (current.x-click.x)^2+(current.y-click.y)^2 on stack
	fild qword [rsp] ; put rcx to st0, st1 = PEROID
	pop rcx ; poping to restore rsp
	fsqrt ; sqrt of rcx ((current.x-click.x)^2 + (current.y-click.y)^2) 
	fldpi ; st0 = pi, st1 = sqrt(c) st2 = PEROID
	fdivp ; divided sqrt(c) by pi and store in st1 ( st0 is pi st1 value of sqrt(c)/pi, st2 = PEROID) and pop st0
	
	push word 2
	fidiv word [rsp] ; division by 2
	add rsp, 2
	push word 20 ; PEROID
	fimul word [rsp] ; st0 = sqrt(c)/2pi*PEROID st1 = PEROID
	add rsp, 2
	fprem1 ; st0 =  sqrt(c)/2pi*PEROID%PEROID st1 = PEROID
	fstp st1 ; st0 = sqrt(c)/2pi*PEROID%PEROID
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
