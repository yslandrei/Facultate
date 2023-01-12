bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

; 19) Se dau 2 siruri de octeti A si B. Sa se construiasca sirul R care sa contina doar elementele pare si negative din ;     cele 2 siruri.
; Exemplu:
;  A: 2, 1, 3, -3, -4, 2, -6
;  B: 4, 5, -5, 7, -6, -2, 1
;  R: -4, -6, -6, -2

a db 2, 1, 3, -3, -4, 2, -6
la equ $ - a
b db 4, 5, -5, 7, -6, -2, 1
lb equ $ - b
r resb la + lb

; our code starts here
segment code use32 class=code
    start:
        mov ecx, la
        mov esi, a
        mov edi, r
        
        jecxz endRepeta1
        repeat1:
            lodsb
            cmp al, 0
            jnl endif1 ; negativ - continua, pozitiv - trece la urm
                mov bl, al
                and al, 00000001b
                cmp al, 1
                je endif1 ; par - continua, par - trece la urm
                    mov al, bl
                    stosb
            endif1:
        loop repeat1
        endRepeta1:
        
        mov ecx, lb
        mov esi, b
        
        jecxz endRepeta2
        repeat2:
            lodsb
            cmp al, 0
            jnl endif2 ; negativ - continua, pozitiv - trece la urm
                mov bl, al
                and al, 00000001b
                cmp al, 1
                je endif2 ; par - continua, par - trece la urm
                    mov al, bl
                    stosb
            endif2: 
        loop repeat2
        endRepeta2:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
