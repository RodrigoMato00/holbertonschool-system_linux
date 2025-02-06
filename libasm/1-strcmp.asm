BITS 64

global asm_strcmp

section .text
asm_strcmp:
    push rbp
    mov rbp, rsp
    push r8

    xor r8, r8                   ; r8 = 0

.scan_loop:
    mov al, [rdi + r8]
    mov bl, [rsi + r8]

    test al, al                  ; Check if s1 end (null terminator)
    jz .exit_cmp
    test bl, bl                  ; Check if s2 end
    jz .exit_cmp
    cmp al, bl                   ; Compare both chars
    jne .exit_cmp                ; If differ go decide result

    inc r8                       ; If same move to next char
    jmp .scan_loop

.exit_cmp:
    cmp al, bl
    je .is_equal
    jl .is_less
    jg .is_greater

.is_equal:
    xor rax, rax                 ; Return 0
    jmp .finish

.is_less:
    mov rax, -1                  ; Return -1
    jmp .finish

.is_greater:
    mov rax, 1                   ; Return 1
    jmp .finish

.finish:
    pop r8                       ; Restore r8
    mov rsp, rbp
    pop rbp                      ; Restore pointer
    ret                          ; Done
