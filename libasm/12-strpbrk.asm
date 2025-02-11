BITS 64

global asm_strpbrk

section .text
asm_strpbrk:
  push rbp                   ; Save bp
  mov rbp, rsp
  xor rax, rax               ; Clear rax

  mov r10, rdi               ; s -> r10
  mov r11, rsi               ; Accept -> r11
.loop:
  movzx r8, byte [r10]       ; Load *s into r8
  cmp r8b, 0                 ; If *s == 0 -> end
  je .end
  push r11                  ; Push accept pointer
  push r10                  ; Push current s pointer

  mov rdi, r11              ; rdi = accept
  mov rsi, [rsp]            ; rsi = current s pointer
  movzx rsi, byte [rsi]     ; Load char from s
  jmp .helper               ; Jump to helper
.chr_ret:
  pop r10                   ; Pestore s pointer
  pop r11                   ; Pestore accept pointer
  test rax, rax             ; If rax ≠ 0 -> break
  jnz .found
  inc r10                   ; s++
  jmp .loop
.found:
  mov rax, r10             ; Result = pointer to s where found
  jmp .end
.end:
  mov rsp, rbp
  pop rbp                  ; Restore bp
  ret
.helper:
  push rbp                 ; Save bp (helper)
  mov rbp, rsp
  xor rax, rax             ; Clear rax
.chr_loop:
  mov al, byte [rdi]       ; Load char from accept
  cmp byte [rdi], sil      ; If *accept == c -> found
  jz .chr_found
  cmp byte [rdi], 0        ; If end of accept -> not found
  jz .chr_end
  inc rdi
  jmp .chr_loop
.chr_found:
  mov rax, rdi            ; Found: rax = pointer in accept
.chr_end:
  mov rsp, rbp
  pop rbp                 ; Restore bp
  jmp .chr_ret
