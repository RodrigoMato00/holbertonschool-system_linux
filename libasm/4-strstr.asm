BITS 64

global asm_strstr

section .text
asm_strstr:
    push rbp
    mov rbp, rsp
    push r8
    push r9

    mov al, [rsi]
    test al, al
    jz .needle_empty

.outer:
    mov al, [rdi]              ; Load char haystack
    test al, al
    jz .not_found              ; If end, not found
    mov r8, rdi                ; candidate = current haystack ptr
    mov r9, rsi                ; r9 = ptr

.inner:
    mov al, [r8]               ; candidate char
    mov bl, [r9]               ; needle char
    test bl, bl
    jz .found                ; If needle ended, match found
    test al, al
    jz .no_match             ; If haystack ended, no match
    cmp al, bl
    jne .no_match            ; If mismatch, no match
    inc r8                   ; Next candidate char
    inc r9                   ; Next needle char
    jmp .inner

.no_match:
    inc rdi                ; Advance haystack ptr
    jmp .outer

.found:
    mov rax, rdi           ; Result = candidate ptr
    jmp .finish

.needle_empty:
    mov rax, rdi           ; Result = haystack ptr

.not_found:
    xor rax, rax           ; Result = 0

.finish:
    pop r9                 ; Restore r9
    pop r8                 ; Restore r8
    mov rsp, rbp
    pop rbp                ; Restore rbp
    ret                    ; End
