%define getrandom 318
%define GRND_RANDOM 2
section .data

section .text
    global ft_random
    extern printf

;char *ft_random(char *buf, int size)
ft_random:
	push rbp
	mov rbp, rsp
	mov rdx, GRND_RANDOM
	mov rax, getrandom
	syscall
	leave
	ret
