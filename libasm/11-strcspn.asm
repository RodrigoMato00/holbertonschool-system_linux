BITS 64

global asm_strcspn

section .text
asm_strcspn:
  push rbp                   ; Save bp
  mov rbp, rsp
  xor rcx, rcx               ; count = 0
.loop_strcspn:
  cmp byte [rdi], 0          ; If *s == 0 -> break
  je .end_strcspn
  xor rax, rax               ; Clear rax
  push rsi                   ; Push reject pointer
  push rdi                   ; Push current s pointer

  mov rdi, rsi               ; rdi = reject
  mov rsi, [rsp]             ; rsi = current s pointer
  movzx rsi, byte [rsi]      ; load char from s
  jmp .asm_strchr            ; Jump to helper
.strchr_return:
  pop rdi                    ; Restore s pointer
  pop rsi                    ; Restore reject pointer
  test rax, rax              ; If rax ≠ 0 -> break
  jnz .end_strcspn
  inc rcx                   ; count++
  inc rdi                   ; s++
  jmp .loop_strcspn
.end_strcspn:
  mov rax, rcx              ; Return count
  mov rsp, rbp
  pop rbp                   ; Restore bp
  ret
.asm_strchr:
  push rbp                  ; Save bp
  mov rbp, rsp
  xor rax, rax              ; clear rax
.strchr_loop:
  mov al, byte [rdi]        ; load char from reject
  cmp byte [rdi], sil       ; If *reject == c -> found
  jz .chr_found
  cmp byte [rdi], 0         ; If end of reject -> not found
  jz .chr_end
  inc rdi
  jmp .strchr_loop
.chr_found:
  mov rax, rdi             ; Found: rax = pointer in reject
.chr_end:
  mov rsp, rbp
  pop rbp                  ; Restore bp
  jmp .strchr_return       ; Jump back to caller
