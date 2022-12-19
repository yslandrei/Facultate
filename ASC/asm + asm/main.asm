;Se citesc mai multe siruri de caractere. Sa se determine daca primul apare
;ca subsecventa in fiecare din celelalte si sa se dea un mesaj corespunzator
bits 32
global start

extern exit, scanf, printf
extern strstr

import exit msvcrt.dll    
import printf msvcrt.dll   
import scanf msvcrt.dll 

segment data use32 class=data public

firstString times 16 db 0
otherString times 16 db 0
apearences dd 0
strings dd 0
formatString db '%s', 0
print1 db 'Introduceti un sir ce va fi cautat in sirurile introduse ulterior: ', 0
print2 db 'Introduceti alt sir(0 pentru a iesi): ', 0
printCorrect db 'Primul sir a fost regasit ca secventa in toate celelalte siruri', 0
printWrong db 'Primul sir nu a fost regasit ca secventa in toate celelalte siruri', 0

segment code use32 class=code public

start:
    ;printf("%s", &print1)
    push dword print1
    push dword formatString
    call [printf]
    add esp, 4 * 2
    
    ;scanf("%s", &firstString)
    push dword firstString
    push dword formatString
    call [scanf]
    add esp, 4 * 2
    
    repeat1:
        ;printf("%s", &print2)
        push dword print2
        push dword formatString
        call [printf]
        add esp, 4 * 2
        
        ;scanf("%s", &otherString)
        push dword otherString
        push dword formatString
        call [scanf]
        add esp, 4 * 2
        
        cmp byte[otherString], '0'
        je break
        
        push dword firstString
        push dword otherString
        call strstr; returns 1 in ecx if firstString is present in otherString and 0 contrary
        
        add [apearences], ecx
        add dword[strings], 1
        
    jmp repeat1
    break:
    
    mov eax, [apearences]
    cmp eax, [strings]
    
    je presentInAll
        ;printf("%s", &printWrong)
        push dword printWrong
        push dword formatString
        call [printf]
        add esp, 4 * 2
        jmp final      
    presentInAll:
        ;printf("%s", &printCorrect)
        push dword printCorrect
        push dword formatString
        call [printf]
        add esp, 4 * 2 
    final:
    push dword 0
    call [exit]