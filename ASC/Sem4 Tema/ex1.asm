bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s dw 1234h, 5678h, 9876h
    ls equ ($ - s) / 2
    a dw 0

; Se da un sir de cuvinte. Sa se adune in cuvantul a numarul
; format din bitii 6-9 din fiecare cuvant al sirului
segment code use32 class=code
    start:
        mov ESI, 0
        bucla:
            mov DX, [s + 2 * ESI]
            and DX, 0000001111000000b
            shr DX, 6
            add [a], DX
            inc ESI
            cmp ESI, ls
            jb bucla
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
