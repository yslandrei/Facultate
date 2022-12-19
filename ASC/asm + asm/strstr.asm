bits 32
global strstr

segment code use32 class=code public

strstr:
    
    mov edi, [esp + 8] ;firstString
    mov esi, [esp + 4] ;otherString (bigger one)
    mov ebx, esi
    
    cld
    repeat1:
        mov al, [esi]
        mov ah, [edi]
        cmp al, ah
        je count
        ;dontCount:
            mov esi, ebx
            inc esi
            mov edi, [esp + 8]
            mov ebx, esi
            jmp myendif
        count:
            inc esi
            inc edi
        myendif:  
        cmp byte[edi], 0
        je found
        
        cmp byte[esi], 0
        je notFound
    jmp repeat1
    
    notFound:
        mov ecx, 0
        jmp final
    found:
        mov ecx, 1
    final:
    
ret 4 * 3