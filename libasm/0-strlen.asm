BITS 64

global asm_strlen

section .text
asm_strlen:
    xor rax, rax              ; Initialize to 0

.loop:                        ; Loop
    mov dl, byte [rdi + rax]  ; Load the current byte in DL
    cmp dl, 0                 ; Compare the byte with 0
    je .end                   ; If zero, jump to the end
    inc rax                   ; ++ counter
    jmp .loop                 ; Repeat

.end:                         ; End
    ret                       ; Return
