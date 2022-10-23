bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 19) b + a - (4 - d + 2) + c + (a - b)
    
    a dw 5
    b dw 3
    c dw 4
    d dw 3

; our code starts here
segment code use32 class=code
    start:
        
        mov bx, [b] ; bx = b
        add bx, [a] ; bx = b + a
        mov cx, 4 ; cx = 4
        sub cx, [d]; cx = 4 - d
        add cx, 2; cx = 4 - d + 2
        sub bx, cx ; bx = b + a - (4 - d + 2)
        add bx, [c] ; bx = b + a - (4 - d + 2) + c
        mov cx, [a] ; cx = a
        sub cx, [b] ; cx = a - b
        add bx, cx ; bx = b + a - (4 - d + 2) + c + (a - b)
 
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
