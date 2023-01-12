bits 32
global _printAscii

extern _printf

segment data public data use32

formatC db "%c", 0

segment code public code use32

_printAscii:
    push ebp
    mov ebp, esp

    ;printf(&formatC, [esp + 8])
    push dword [esp + 8]
    push dword formatC
    call _printf
    add esp, 4 * 2

    mov esp, ebp
    pop ebp
ret