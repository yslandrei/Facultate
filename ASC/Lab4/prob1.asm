bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 2
    b dd -8
    c dw -5
    d dq 12
    ;7 / a - b + (-c) * (-2) + d

; our code starts here
segment code use32 class=code
    start:
        MOV AX, 7
        MOV BL, [a]
        IDIV BL; AL = 7 / a
        MOVSX EAX, AL; EAX = 7 / a
        SUB EAX, [b]; EAX = 7 / a - b
        MOV ECX, EAX; ECX = 7 / a - b
        MOV AX, 0
        SUB AX, [c]; AX = -c
        MOV DX, -2; DX = -2
        IMUL DX; DX:AX = (-c) * (-2)
        PUSH DX
        PUSH AX 
        POP EAX; EAX = (-c) * (-2)
        ADD ECX, EAX; ECX = 7 / a - b + (-c) * (-2)
        MOV EAX, dword[d + 4]
        MOV EBX, dword[d];EAX:EBX = d
        add EBX, ECX
        adc EAX, 0;EAX:EBX = 7 / a - b + (-c) n
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
s