section .data

str:
	db "Woody", 10, 0

section .text

global main

main:
	push rbp
	mov rbp, rsp
	mov rdi, 1
	lea rsi, [rel str]
	mov rdx, 6
	mov rax, 0x01
	syscall
	leave
	ret

