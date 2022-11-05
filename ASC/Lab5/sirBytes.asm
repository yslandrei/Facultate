bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de bytes
    ; Sa se salveze intr-un sir doar bytes care au ultima cifra egala cu 7 
    ; s=(27, 17, 23, 12, 07h, 13) => d = (27, 17, 07h)
    
    s db 27, 17, 23, 12, 07h, 13
    ls equ $-s
    d resb ls ; se rezerva in mem ls bytes pentru sirul d
    detest db -1 ; doar pt delimitare sir output in memorie pt a vedea in debugger

; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls
        mov esi, 0
        mov edi, 0
        repeta:
            mov al, byte[s + ESI]
            mov dl, al
            movzx ax, al
            mov bl, 10
            div bl; ah - rest
            cmp ah, 7
            je salveaza
            jne next
                salveaza:
                    mov byte[d+edi], dl
                    inc edi
                    ;inc esi
                    ;jmp myendif
                next:
                    inc esi
                    ;myendif:
        loop repeta
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
