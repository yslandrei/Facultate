bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de doubleworduri
    ; Sa se inverseze acest sir
    ; s = (10, 11, 12) => d = (12, 11, 10)
    s dd 10, 11, 12
    ls equ ($ - s) / 4
    d resd ls

; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls
        mov esi, (ls - 1) * 4 ; pentru parcurgerea lui s de la dr la st
        mov edi, 0            ; pentru parcurgerea lui d de la st la dr
        repeta:
            mov eax, dword[s + esi]
            mov dword[d + edi], eax
            add edi, 4
            sub esi, 4
        loop repeta
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
