;STACK
;adr de revenire - ESP
;maxim           - ESP + 4
;arr             - ESP + 8
;arrLen          - ESP + 12


bits 32
global max

segment code use32 class=data public

max:
    mov esi, [esp + 8]
    mov ebx, [esi] ; ebx = maximum (initialized as first element of the array)
    mov ecx, [esp + 12]

    jecxz over
    repeat1:
        lodsd
        cmp eax, ebx
        jng isNotMax
        ;isMax:
            mov ebx, eax
        isNotMax:
    loop repeat1
    over:

    mov [esp + 4], ebx
ret
