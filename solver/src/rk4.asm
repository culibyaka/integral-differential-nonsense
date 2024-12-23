bits 64
default rel

section .text
global SolveStep

kHalf   dd 0.5
kTwo    dd 2.0
kSix    dd 6.0

SolveStep:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 48

    mov     qword [rbp-8], rdi  ; Func pointer
    mov     qword [rbp-44], rsi  ; ctx pointer
    movss   dword [rbp-12], xmm0  ; t
    movss   dword [rbp-16], xmm1  ; y
    movss   dword [rbp-20], xmm2  ; dt

    ;; ------------------   k1    -----------------

    mov     rdi, qword [rbp-44]
    call    qword [rbp-8]
    movss   dword [rbp-24], xmm0  ; k1

    ;; ------------------   k2    -----------------

    ; FIXME: store dt/2 at reg/mem
    movss   xmm2, dword [rbp-20]  ; dt
    mulss   xmm2, dword [kHalf]   ; dt/2
    
    movss   xmm0, dword [rbp-12]
    addss   xmm0, xmm2  ; t + dt/2

    movss   xmm1, [rbp-24]
    mulss   xmm1, xmm2
    addss   xmm1, dword [rbp-16]

    mov     rdi, qword [rbp-44]
    call    qword [rbp-8]
    movss   dword [rbp-28], xmm0 ; k2

    ;; ------------------   k3    -----------------

    movss   xmm2, dword [rbp-20]  ; dt
    mulss   xmm2, dword [kHalf]   ; dt/2
    
    movss   xmm0, dword [rbp-12]
    addss   xmm0, xmm2  ; t + dt/2

    movss   xmm1, [rbp-28]
    mulss   xmm1, xmm2
    addss   xmm1, dword [rbp-16]

    mov     rdi, qword [rbp-44]
    call    qword [rbp-8]
    movss   dword [rbp-32], xmm0 ; k3

    ;; ------------------   k4    -----------------

    movss   xmm0, dword [rbp-12]
    addss   xmm0, dword [rbp-20]  ; t + dt

    movss   xmm1, dword [rbp-32]
    mulss   xmm1, dword [rbp-20]
    addss   xmm1, dword [rbp-16]

    mov     rdi, qword [rbp-44]
    call    qword [rbp-8]
    movss   dword [rbp-36], xmm0 ; k4

    ;; ------------------   avg   -----------------

    movss   xmm1, dword [rbp-24]

    movss   xmm2, dword [rbp-28]
    mulss   xmm2, dword [kTwo]

    movss   xmm3, dword [rbp-32]
    mulss   xmm3, dword [kTwo]

    movss   xmm4, dword [rbp-36]

    movss   xmm0, xmm1
    addss   xmm0, xmm2
    addss   xmm0, xmm3
    addss   xmm0, xmm4
    mulss   xmm0, dword [rbp-20]
    divss   xmm0, dword [kSix]
    addss   xmm0, dword [rbp-16]

    add     rsp, 48
    pop     rbp
    ret