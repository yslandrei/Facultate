bits 32
global suma

segment code use32 class=code public

suma:
    mov eax, [esp + 12]
    add eax, [esp + 8]
    mov [esp + 4], eax
    ;Stiva:
    ;adr de revenire - ESP
    ;x               - ESP + 4
    ;b               - ESP + 8
    ;a               - ESP + 12