bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se da un sir de QWord uri. Se da o constanta k
    ; Sa se aduna const k la fiecare QWord din s
    ;s dq 1122334455667788h, 10 => in memorie: 88 77 66 55 44 33 22 11/ 0A 00 00 00 00 00 00 00
    s dq 0, 1, 2
    ls equ ($ - s) / 8
    r resq ls
    k equ 5
    d resq ls; 5 6 7
    
; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls
        mov esi, 0
        repeta:
            mov eax, dword[s + esi + 0]
            mov edx, dword[s + esi + 4]
            add eax, k
            adc eax, 0
            mov dword[d + esi + 0], eax
            mov dword[d + esi + 4], edx
            add esi, 8
        loop repeta:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
