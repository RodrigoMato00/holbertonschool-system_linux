; 0-strlen.asm
; Function: asm_strlen
; length of a string.
; Input:
;   RDI -> pointer to the string.
; Output:
;   RAX = length of the string type size_t.

global asm_strlen

section .text
asm_strlen:
    xor rax, rax              ; Initialize RAX in 0
start:
    mov dl, byte [rdi + rax]  ; Load byte into DL
    cmp dl, 0                 ; Compare byte 0
    je end                    ; 0 jump to end
    inc rax                   ; ++ counter
    jmp start                 ; Loop to start
end:
    ret                       ; Return length in RAX

