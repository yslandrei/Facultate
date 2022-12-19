bits 32
global concatenare

;.
;.
;.

segment code use 32 class=data public

concatenare:
    mov esi, [ESP + 12]
    mov edi, [ESP + 4]
    cld
    repeta:
        lodsb
        jz next
        stosb
    jmp repeta
    next:
    
    mov esi, [ESP + 8]
    repeta2:
        lodsb 
        jz next2
        stosb
    jmp repeta2
    next2:
ret