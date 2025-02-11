BITS 64

global asm_putc

section .text
asm_putc:
    push rbp                   ; Save rbp
    mov rbp, rsp
    push rdi                   ; Save the c in stack

    mov rax, 1                 ; Syscall write
    mov rdi, 1                 ; Stdout 1
    mov rsi, rsp               ; Pointer to the char in stack
    mov rdx, 1                 ; Number of bytes 1
    syscall                    ; Write syscall

    mov rsp, rbp               ; restore rsp
    pop rbp                    ; restore rbp
    ret                        ; End
