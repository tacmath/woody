section .text

global main
main:
	push rax
	push rbx
	push rcx
	push rdx
	push rsi
	push rdi
	jmp print_woody
decode:
	lea rdi, [rel fin]
	mov rsi, 0
	lea rdx, [rel key]
	mov rcx, 0
	jmp decrypt

print_woody:
	mov rdi, 1
	lea rsi, [rel woody] 
	mov rdx, 14
	mov rax, 0x01
	syscall
	jmp decode
woody: db "....WOODY....", 10

decrypt:
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
fin:
	pop rdi
	pop rsi
	pop rdx
	pop rcx
	pop rbx
	pop rax
	jmp 10
key: db 0
