bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    s dq 0101000000000001h, 050A000000000000h
    ls equ ($ - s) / 8
    d resb ls * 8

; our code starts here
segment code use32 class=code
    start:
        
        mov ecx, ls * 8
        mov esi, s
        mov edi, d
        cld
        clc
        mov bl, 0 ; lungimea lui d 
        
        jecxz endRepeat1
        repeat1:
            lodsb
            mov bl, 0 ; nr de biti 1 intr un byte
            mov edx, 7
            repeat2:
                shr al, 1
                adc bl, 0
                dec edx
                cmp edx, 0
            jne repeat2
            mov al, bl
            stosb
        loop repeat1
        endRepeat1:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
