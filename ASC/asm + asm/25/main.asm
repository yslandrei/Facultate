;Se citeste de la tastatura un sir de numere in baza 10, cu semn. Sa se determine
;valoarea maxima din sir si sa se afiseze in fisierul max.txt (fisierul va fi creat) valoarea maxima, in baza 16
bits 32
global start

extern exit, scanf, printf, fprintf, fopen, max

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll

segment data use32 class=data public

arr resd 64
arrLen dd 0
maxim dd 0
fileName db "max.txt", 0
descr dd 0
accesMode db "w", 0
scanFormat db "%d", 0
printFormat db "Maximul in baza 16 este: %x", 0
printMsg1 db "Introduceti lungimea sirului: ", 0
printMsg2 db "Introduceti sirului: ", 0

segment code use32 class=data public

start:
    ;printf(&printMsg1)
    push dword printMsg1
    call [printf]
    add esp, 4 * 1

    ;scanf(&scanFormat, &arrLen)
    push dword arrLen
    push dword scanFormat
    call [scanf]
    add esp, 4 * 2

    ;printf(&printMsg2)
    push dword printMsg2
    call [printf]
    add esp, 4 * 1

    mov ecx, [arrLen]
    mov esi, arr
    jecxz over
    read1:
        push ecx
        push dword esi
        push dword scanFormat
        call [scanf]
        add esp, 4 * 2 
        add esi, 4
        pop ecx
    loop read1
    over:

    push dword [arrLen]
    push dword arr
    push dword [maxim]
    call max
    mov ebx, [esp]
    mov [maxim], ebx
    add esp, 4 * 3

    ;fopen(&fileName, &accesMode)
    push dword accesMode
    push dword fileName
    call [fopen]
    add esp, 4 * 2

    mov [descr], eax
    cmp dword [descr], 0
    je final

    ;fprintf(descr, &printFormat, maxim)

    push dword [maxim]
    push dword printFormat
    push dword [descr]
    call[fprintf]
    add esp, 4 * 3

    final:
    push dword 0
    call [exit]



    