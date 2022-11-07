bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 2, 1, -3, 3, -4, 2, 6
    la equ $ - a
    b db 4, 5, 7, 6, 2, 1
    lb equ $ - b
    r resb la + lb

; Se dau 2 siruri de octeti A si B. Sa se construiasca sirul R care sa contina elementele lui B in ordine inversa urmate de elementele negative ale lui A
segment code use32 class=code
    start:
        mov ecx, lb
        mov esi, lb - 1
        mov edi, 0
        repeta1:
            mov al, [b + esi]
            mov [r + edi], al
            dec esi
            inc edi
        loop repeta1
        
        mov ecx, la
        mov esi, 0
        repeta2:
            mov al, [a + esi]
            cmp al, 0
            jl salveaza
            jge next
            salveaza:
                mov [r + edi], al
                inc edi
                inc esi
                jmp myendif
            next:
                inc esi
                myendif:
        loop repeta2
        
        
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
