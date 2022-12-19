; Scrieti un program in limbaj de asamblare care prin intermediul unei proceduri
; concateneaza doua siruri de caractere si apoi afiseaza rez pe ecran  

bits 32
global start
import exit msvcrt.dll
extern exit
extern printf, concatenare
import pritf msvcrt.dll

segment data use32 class=data public
    s1 db 'abc', 0
    s2 db 'defgh', 0
    lDest equ $ - s1 - 1
    dest resb lDest
    
segment code use 32 class=data public

start:
    push dword s1
    push dword s2
    push dword lDest
    
    call concatenare
    add esp, 4 * 3
    
    push dword dest
    push dword format
    call [printf]
    add esp, 4 * 2
    
    push dword 0
    call [exit]