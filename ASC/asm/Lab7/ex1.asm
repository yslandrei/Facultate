bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de bytes cu elem neg si pozitive
    ; Sa se extraga elementele neg in sirul n
    ; Sa se extraga elementele poz in sirul p
    
    s db 1, -2, 3, -2, 4 ;=> n = -2, -2; p = 1, 3, 4 ; esi
    ls equ $-s
    n resb ls ; edi
    p resb ls ; edp

; our code starts here
segment code use32 class=code
    start:
        
        mov esi, s; mov esi, 0
        mov edi, n; mov edi, 0
        mov epd, p; mov edp, 0
        mov ecx, ls
        cld ; stabilire dir de parcurgere
        repeta:
            ; mov al, [s + esi]
            ; inc esi
            lodsb
            cmp al, 0
            jge pozitiv
            jl negativ
                pozitiv:
                    ; mov [p + ebp], al
                    ;inc ebp
                    xchg edi, ebp
                    stosb
                    xchg edi, ebp
                jmp myendif
                negativ:
                    ; mov [n + edi], al
                    ; inc edi
                    stosb
                myendif:
        loop repeta
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
