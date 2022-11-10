bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    a dw 1111111111111111b
    b dw 0000000000000000b
    c dd 0

;12) Se dau doua cuvinte A si B. Sa se obtina dublucuvantul C: = 1111 1111 1111 1111 0000 0011 1000 0000b = FFFF0380h
;       bitii 0-6 ai lui C au valoarea 0
;       bitii 7-9 ai lui C coincid cu bitii 0-2 ai lui A
;       bitii 10-15 ai lui C coincid cu bitii 8-13 ai lui B
;       bitii 16-31 ai lui C au valoarea 1
segment code use32 class=code
    start:
        ;1. bitii 0-6 ai lui C au valoarea 0
        or dword[c], 00000000000000000000000000000000b; (sunt deja 0)
        
        ;2. bitii 7-9 ai lui C coincid cu bitii 0-2 ai lui A
        mov AX, [a]
        and AX, 0000000000000111b; AX: 0000 0000 0000 0111
        movzx EAX, AX; EAX: 0000 0000 0000 0000 0000 0000 0000 0111
        shl EAX, 7;    EAX: 0000 0000 0000 0000 0000 0011 1000 0000
        or dword[c], EAX
        
        ;3. bitii 10-15 ai lui C coincid cu bitii 8-13 ai lui B
        mov BX, [b]
        and BX, 0011111100000000b; BX: 0011 1111 0000 0000
        movzx EBX, BX; EBX: 0000 0000 0000 0000 0011 1111 0000 0000
        shl EBX, 2;    EBX: 0000 0000 0000 0000 1111 1100 0000 0000
        or dword[c], EBX
        
        ;4. bitii 16-31 ai lui C au valoarea 1
        or dword[c], 11111111111111110000000000000000b
        
        
        mov EAX, [c]; debugging
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
