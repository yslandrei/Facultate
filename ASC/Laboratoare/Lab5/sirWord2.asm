bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;Se da un sir de worduri. Sa se salveze doar bytes superiori care sunt divizibili cu 8
    
    s dw 0808h, 0abcdh
    ls equ ($ - s) / 2
    d resb ls
; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls
        mov esi, 1; s
        mov edi, 0; d
        repeta:
            mov al, byte[s+esi]
            mov dl, al
            movsx ax, al
            mov bl 8
            idiv bl
            cmp ah, 0
            je adauga
            je next
                adauga:
                    mov byte[d+edi], dl
                    inc edi
                    add esi, 2
                    jmp myendif:
                next:
                    add esi, 2
                myendif:
            
        loop repeta
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
