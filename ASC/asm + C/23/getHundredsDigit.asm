bits 32
global _getHundredsDigit

segment data public data use32

suta dw 100
zece dw 10

segment code public code use32

_getHundredsDigit:
    push ebp
    mov ebp, esp

    mov ax, [esp + 8]
    mov dx, [esp + 10]
    div word[suta] ; / 100
    mov dx, 0
    div word[zece] ; % 10
    movzx eax, dx

    mov esp, ebp
    pop ebp
ret