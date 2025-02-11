BITS 64

global asm_strncmp

section .text
asm_strncmp:
    ; Start: save rbp and r8 we need them
    push rbp
    mov rbp, rsp
    push r8

    xor r8, r8                   ; r8 = 0

.loop_strncmp:
    cmp rdx, 0                   ; if n is 0
    je .finish_equal

    mov al, [rdi + r8]           ; Load the current byte in AL
    mov bl, [rsi + r8]           ; Load the current byte in BL

    cmp al, 0
    je .compute_diff
    cmp bl, 0
    je .compute_diff
    cmp al, bl                   ; Compare characters
    jne .compute_diff            ; If not equal

    inc r8                       ; Go to next character
    dec rdx                      ; Decreased n
    jmp .loop_strncmp

.compute_diff:
    movzx eax, al           ; 0 extend s1 char into eax
    movzx edx, bl           ; 0 extend s2 char into edx
    sub eax, edx            ; eax = eax - edx, the difference
    jmp .finish

.finish_equal:
    xor eax, eax           ; All n chars compared and same, return 0

.finish:
    pop r8                 ; Restore r8
    mov rsp, rbp
    pop rbp                ; Restore pointer
    ret			   ;End
