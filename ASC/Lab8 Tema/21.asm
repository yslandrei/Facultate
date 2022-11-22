bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

;21.Se dau 2 siruri de octeti A si B. Sa se construiasca sirul R care sa contina elementele lui B in ordine inversa 
;   urmate de elementele negative ale lui A.
; Exemplu:
;  A: 2, 1, -3, 3, -4, 2, 6
;  B: 4, 5, 7, 6, 2, 1
;  R: 1, 2, 6, 7, 5, 4, -3, -4

a db 2, 1, -3, 3, -4, 2, 6
la equ $ - a
b db 4, 5, 7, 6, 2, 1
lb equ $ - b
r resb la + lb

segment code use32 class=code
    start:
        
        mov ecx, lb
        mov esi, b + lb - 1
        mov edi, r
        
        jecxz endRepeat1
        repeat1:
            std
            lodsb ; al = b[esi], esi --
            cld
            stosb ; r[edi] = al, edi ++
        loop repeat1
        endRepeat1:
        
        mov ecx, la
        mov esi, a
        cld
        
        jecxz endRepeat2
        repeat2:
            lodsb ; al = a[esi], esi ++
            cmp al, 0
            jnl endIf1
                stosb ; r[edi] = al, edi ++
            endIf1:
        loop repeat2
        endRepeat2:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
