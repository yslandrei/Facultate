bits 32
global suma
extern a, b, x

segment code use32 class=code public

suma:
    mov al, [a]
    add al, [b]
    mov [x], al
ret