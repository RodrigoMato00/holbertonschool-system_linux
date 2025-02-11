BITS 64
global asm_strncasecmp

section .text
asm_strncasecmp:
    push rbp                   ; Save bp
    mov rbp, rsp
    push rdx                   ; Save rdx

    mov r15, rdx               ; n -> r15
    cmp r15, 0                 ; If n == 0 -> finish
    je .finish_zero
.while:
    cmp r15, 0                 ; If n == 0 -> break
    je .after
    mov rax, rdi               ; a_ptr = s1
    mov rdx, rsi               ; b_ptr = s2
    movzx eax, byte [rax]      ; a = s1[i]
    movzx edx, byte [rdx]      ; b = s2[i]
    cmp al, 0                  ; If a == 0 -> break
    je .after
    cmp dl, 0                  ; If b == 0 -> break
    je .after
    cmp al, 65                 ; If a >= 'A'
    jl .skip_a
    cmp al, 90                 ; If a <= 'Z'
    jg .skip_a
    add al, 32                 ; a = a + 32
.skip_a:
    cmp dl, 65                 ; If b >= 'A'
    jl .skip_b
    cmp dl, 90                 ; If b <= 'Z'
    jg .skip_b
    add dl, 32                 ; b = b + 32
.skip_b:
    cmp al, dl                 ; a ?= b
    jne .after                 ; If a ≠ b -> break
    inc rdi                    ; s1++
    inc rsi                    ; s2++
    dec r15                    ; n--
    jmp .while
.after:
    cmp al, dl                 ; If a == b -> result = 0
    je .equal
    jl .less                   ; If a < b
    sub al, dl                 ; Result = a - b
    jmp .finish
.equal:
    mov rax, 0                 ; Result = 0
    jmp .finish
.less:
    sub al, dl                 ; Result = a - b
    neg al                     ; Result = -(a - b)
    imul eax, -1               ; Adjust sign
    jmp .finish
.finish_zero:
    mov rax, 0                 ; Result = 0 (n == 0)
.finish:
    pop rdx                    ; Restore rdx
    mov rsp, rbp
    pop rbp                    ; Restore bp
    ret                        ; End
  