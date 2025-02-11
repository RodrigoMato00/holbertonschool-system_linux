BITS 64

global asm_memcpy

section .text
asm_memcpy:
    push rbp                  ; Save rbp
    mov rbp, rsp
    push rdi                  ; Save dest

.copy_loop:
    test rdx, rdx             ; If n==0 end
    jz .done
    dec rdx                   ; n--
    mov al, [rsi]             ; Load byte src
    mov [rdi], al             ; Store byte in dest
    inc rdi                   ; dest++
    inc rsi                   ; src++
    jmp .copy_loop

.done:
    pop rax                   ; Restore dest in rax
    mov rsp, rbp
    pop rbp                   ; Restore rbp
    ret                       ; End
