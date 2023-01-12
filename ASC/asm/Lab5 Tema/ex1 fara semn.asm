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
    c db 3
    b dw 6
    d dd 21
    x dq 30
    
    ;12) (a*b+2)/(a+7-c)+d+x (fara semn) = 53
; our code starts here
segment code use32 class=code
    start:
        movzx AX, byte[a]
        mov DX, [b]
        mul DX; DX:AX = a*b
        add AX, 2
        adc DX, 0; DX:AX = a*b+2
        mov BL, [a]
        add BL, 7
        sub BL, [c]; BL = a+7-c
        movzx BX, BL; BX = a+7-c
        div BX; AX = (a*b+2)/(a+7-c)
        movzx EAX, AX; EAX = (a*b+2)/(a+7-c)
        add EAX, [d]; EAX = (a*b+2)/(a+7-c)+d
        mov ECX, dword[x + 4]
        mov EBX, dword[x]; ECX:EBX = d
        add EBX, EAX
        adc ECX, 0; ECX:EBX = (a*b+2)/(a+7-c)+d+x
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
