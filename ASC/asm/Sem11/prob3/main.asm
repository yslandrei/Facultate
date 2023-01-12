; Se dau 2 siruri de caractere 
; sa se afiseze sirul cu numar maxim de caractere speciale 

extern nrSpeciale
extern maxSiruri

segment data ... public
    s1 db 'ab./-', 0
    l1 equ $ - s1
    s2 db 's\as;eq.', 0
    l2 equ $ - s2
    format db '%s', 0
    
segment code ... start
    push dword s1
    push dword l1
    push dword 0
    
    call nrSpeciale
    
    pop eax
    add esp, 4 * 2
    
    push dword s2
    push dword l2
    push dword 0
    
    call nrSpeciale
    
    pop ebx
    add esp, 4 * 2
    
    push eax
    push ebx
    push dword 0
    
    call maxSiruri
    
    pop ecx
    add esp, 4 * 2
    
    cmp eax, ecx
    je afis1
    jne afis2
    
    afis1:
        push dword s1
    jmp next
        
    afis2:
        push dword s2
    next:
    
    push dword format
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]