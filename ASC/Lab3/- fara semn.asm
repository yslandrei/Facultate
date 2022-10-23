bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a db 9
    b dw 5
    c dw 4
    d dd 2  

; (a * b) + (c * d) cu semn
; our code starts here
segment code use32 class=code
    start:
        MOVZX AX, byte[a]
        MOV DX, [b]
        MUL DX ; DX:AX = a * b
        PUSH DX
        PUSH AX
        POP EBX ; EBX = a * b
        MOVZX EAX, word[c]
        MOV EDX, [d]
        MUL EDX ;    EDX:EAX = c * d
        MOV ECX, 0 ; ECX:EBX = a * b
        SUB EAX, EBX
        SBB EDX, ECX ; EDX:EAX = (a * b) + (c * d)
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
