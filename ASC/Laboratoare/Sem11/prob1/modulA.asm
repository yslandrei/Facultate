bits 32
global suma

segment code use32 class=code public

suma:
    ; ecx = eax + ebx
    mov ecx, eax
    add ecx, ebx
ret