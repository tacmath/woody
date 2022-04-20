section .data


section .text
	global decrypt

decrypt:
	push rbp
	mov rbp, rsp
    	mov rax, rsi
    	mov r12, rdx
    	xor rdx, rdx
	mov r13, rcx
    	div r13
   	mov r13, rdx
    	mov rdx, r12
	loop:
	cmp r13, 0
	jnz nochange
	mov r13, rcx
	nochange:
    	dec r13
    	dec rsi
	mov bl, byte [rdi+rsi-1]
    	add bl, byte [rdx+r13]
	sub [rdi+rsi], bl
	cmp rsi, 1
	jnz loop
    	mov bl, byte [rdx]
	sub [rdi], bl
	mov rax, rdi
	leave
	ret
