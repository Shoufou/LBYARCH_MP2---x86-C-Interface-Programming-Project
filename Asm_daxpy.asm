section .text
bits 64
default rel

global Asm_daxpy
; r8 - pointer to vectorX
; r9 - pointer to vectorY
; rsp+32 - pointer to vectorZ
; xmm1 - value of A
; ecx - value of N

Asm_daxpy:
    test ecx,ecx
    jle Lend

   mov r11d, ecx
   mov r10, [rsp+40]
   vbroadcastsd ymm0, xmm1
   
   and ecx, ~3
   jz Lscaler

Lloop:
   vmovapd ymm1, [r8]
   vmovapd ymm2, [r9]

   vmulpd ymm1, ymm1, ymm0
   vaddpd ymm1, ymm1, ymm2

   vmovapd [r10], ymm1

   add r8,32
   add r9,32
   add r10, 32

   sub ecx, 4
   jnz Lloop

Lscaler:
    mov ecx, r11d
    and ecx, 3
    jz Lend

Lscalercompute:
    movsd xmm2, [r8]
    movsd xmm3, [r9]

    mulsd xmm2, xmm0
    addsd xmm2, xmm3

    movsd [r10], xmm2

    add r8,8
    add r9,8
    add r10, 8

    dec ecx
    jnz Lscalercompute
    
   Lend:
      vzeroupper
      ret
    