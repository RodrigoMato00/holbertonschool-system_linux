BITS 64

global asm_puts
extern asm_strlen

section .text
asm_puts:
    push rbp
    mov rbp, rsp
    push r15
    push rdi                 ; Save pointer str

    call asm_strlen

    pop rdi
    push rdi

    mov r15, rax             ; Save length in r15

    mov rax, 1               ; Syscall write
    mov rdi, 1               ; Stdout 1
    mov rsi, [rsp]           ; Pointer to str from stack
    mov rdx, r15             ; Length from r15
    syscall

end:
    pop rdi                  ; Remove str from stack
    mov rax, r15             ; Set value = length
    pop r15                  ; restore r15
    mov rsp, rbp
    pop rbp                  ; restore rbp
    ret                      ; End
