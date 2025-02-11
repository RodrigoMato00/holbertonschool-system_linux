BITS 64

global asm_strcasecmp

section .text
asm_strcasecmp:
    push rbp                   ; Save bp
    mov rbp, rsp
    push rdx                   ; Save rdx

.loop:
    mov rax, rdi               ; a_ptr = s1
    mov rcx, rsi               ; b_ptr = s2
    movzx eax, byte [rax]      ; a = s1[i]
    movzx ecx, byte [rcx]      ; b = s2[i]
    cmp al, 0                  ; If a == 0 → break
    je .exit_loop
    cmp cl, 0                  ; If b == 0 → break
    je .exit_loop
.cont_check:
    cmp al, 65                 ; If a ≥ 'A'
    jl .skip_a
    cmp al, 90                 ; If a ≤ 'Z'
    jg .skip_a
    add al, 32                 ; a = a + 32
.skip_a:
    cmp cl, 65                 ; If b ≥ 'A'
    jl .skip_b
    cmp cl, 90                 ; If b ≤ 'Z'
    jg .skip_b
    add cl, 32                 ; b = b + 32
.skip_b:
    cmp al, cl                ; a ?= b
    jne .exit_loop            ; If a ≠ b → break
    inc rdi                   ; s1++
    inc rsi                   ; s2++
    jmp .loop

.exit_loop:
    cmp al, cl                ; If a == b → result = 0
    je .equal
    jl .less                  ; If a < b
    sub al, cl                ; result = a - b
    jmp .finish
.equal:
    mov rax, 0                ; result = 0
    jmp .finish
.less:
    sub al, cl                ; result = a - b
    neg al                    ; result = -(a - b)
    imul eax, -1              ; Adjust sign
    jmp .finish
.finish:
    pop rdx                   ; Restore rdx
    mov rsp, rbp
    pop rbp                   ; Restore bp
    ret                       ; End
