section .data


section .text
	global encrypt

; char	*encrypt(char *data, int dataSize, char	*key, int keySize)
encrypt:
	push rbp
	mov rbp, rsp
	mov r12, 0
	mov r13, 0
	mov bl, byte [rdx+r13]
	add [rdi+r12], bl
	loop:
	inc r13
	cmp r13, rcx
	jnz nochange
	mov r13, 0
	nochange:
	mov bl, byte [rdx+r13]
	add bl, byte [rdi+r12]
	inc r12
	add [rdi+r12], bl
	cmp r12, rsi
	jnz loop
	mov rax, rdi
	leave
	ret