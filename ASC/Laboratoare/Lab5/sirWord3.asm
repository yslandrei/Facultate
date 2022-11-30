bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de worduri (+-). Sa se salveze intr un alt sir de worduri, wordurile care au
    ; suma cifrelor in hexazecimal egala cu o const k

    s dw 1234h, 3412h, 1a2bh
    ls equ ($ - s) / 2
    k equ 0Ah
    d resw ls
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls
        mov esi, 0
        mov edi, 0
        repeta:
            mov ax, [s + esi]
            mov dl, 0
            
            mov bl, byte[s + esi + 0]
            and bl, 00001111b
            add dl, bl
            
            mov bl, byte[s + esi + 0]
            and bl, 11110000b
            shr bl, 4
            add dl, bl
            
            mov bl, byte[s + esi + 1]
            and bl, 00001111b
            add dl, bl
            
            mov bl, byte[s + esi + 1]
            and bl, 11110000b
            shr bl, 4
            add dl, bl ; dl = suma cifrelor
       
            cmp dl, k
            je salveaza
            jne next
            salveaza:
                mov [d + edi], ax
                add edi, 2
                add esi, 2
                jmp myendif
            next:
                add esi, 2
                myendif:
        loop repeta
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
