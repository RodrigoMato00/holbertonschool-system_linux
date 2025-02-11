BITS 64

global asm_strspn

section .text
asm_strspn:
  push rbp                   ; Save bp
  mov rbp, rsp
  xor rcx, rcx               ; count = 0
.loop_spn:
  cmp byte [rdi], 0          ; If *s == 0 -> break
  jz .end_spn
  xor rax, rax               ; Clear rax
  push rsi                   ; Save accept pointer
  push rdi                   ; Save current s pointer

  mov rdi, rsi               ; rdi = accept
  mov rsi, [rsp]             ; rsi = current s pointer
  movzx rsi, byte [rsi]      ; Load current char from s
  jmp .chr_func
.restore:
  pop rdi                    ; Restore s pointer
  pop rsi                    ; Restore accept pointer
  test rax, rax              ; If rax == 0 -> char not found
  jz .end_spn                ; Break
  inc rcx                    ; count++
  inc rdi                    ; s++
  jmp .loop_spn
.end_spn:
  mov rax, rcx               ; Return count
  mov rsp, rbp
  pop rbp
  ret
.chr_func:
  push rbp                   ; Save bp for chr_func
  mov rbp, rsp
  xor rax, rax               ; Clear rax
.chr_loop:
  mov al, byte [rdi]         ; Load char from accept
  cmp byte [rdi], sil        ; Compare with c
  je .chr_found
  cmp byte [rdi], 0          ; If end -> not found
  je .chr_end
  inc rdi
  jmp .chr_loop
.chr_found:
  mov rax, rdi             ; Found: rax = pointer in accept
.chr_end:
  mov rsp, rbp
  pop rbp                  ; Restore bp for chr_func
  jmp .restore
