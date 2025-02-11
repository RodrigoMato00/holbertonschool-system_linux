BITS 64

global asm_strchr

section .text
asm_strchr:
    push rbp                   ; save rbp
    mov rbp, rsp

.loop_strchr:
    mov al, [rdi]              ; Load char from s
    cmp al, sil                ; Cmp with c
    je .found                  ; If eq, jump found
    test al, al                ; Check if null
    jz .not_found              ; If 0, jump not_found
    inc rdi                    ; Next char
    jmp .loop_strchr           ; Loop

.found:
    mov rax, rdi               ; Set result to addr
    jmp .finish

.not_found:
    xor rax, rax               ; Set result to 0

.finish:
    mov rsp, rbp
    pop rbp                    ; Restore rbp
    ret                        ; End
