bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de bytes. Sa se salveze intr -un alt sir bytes, bytes care au valorea impara
    
    s db 17, 12, 13, 6, 7
    ls equ $ - s
    d resb ls
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls
        mov esi, 0
        mov edi, 0
        repeta:
            mov al, [s + esi]
            mov ah, al
            and al, 00000001
            cmp al, 00000001
            je salveaza
            jne next
            salveaza:
                mov [d + edi], ah
                inc esi
                inc edi
                jmp myendif
            next:
                inc esi
                myendif:
        loop repeta
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
