bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit              
extern suma
;b) global a, b, x
import exit msvcrt.dll   
                         

; our data is declared here (the variables needed by our program)
segment data use32 class=data public ; PUBLIC!!!!
    ; a) scrieti un program modular care calculeaza x = a + b cu parametrii transmisi prin registrii
    ; b)                                                         parametrii transmisi prin var globale
    ; c)                                                         parametrii transmisi prin stiva

    a db 18h
    b db -25
    x resb 1
    
; our code starts here
segment code use32 class=code public ; ; PUBLIC!!!!
    start:
        
        movsx eax, byte[a]
        movsx ebx, byte[b]
        movsx ecx, byte[x]
        
        push eax
        push ebx
        push ecx
        
        call suma
        
        pop eax
        mov [x], al
        add esp, 4 * 2 
        
        ;a) mov [x], cl
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
