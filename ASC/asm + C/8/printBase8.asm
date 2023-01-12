bits 32
global _printBase8

extern _printf

segment data public data use32

format8 db "%o", 0

segment code public code use32

_printBase8:
    push ebp
    mov ebp, esp

    ;printf(&format8, [esp + 8])
    push dword [esp + 8]
    push dword format8
    call _printf
    add esp, 4 * 2

    mov esp, ebp
    pop ebp
ret


