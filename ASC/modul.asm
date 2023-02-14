bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global biti        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    biti:
        ;ax = wordul nostru care trb sa-i calculam nr de biti 1
        mov ecx, 16
        mov dl, 0; dl = counter
        repeta:
            shr ax, 1
            adc dl, 0
        loop repeta
    ret
