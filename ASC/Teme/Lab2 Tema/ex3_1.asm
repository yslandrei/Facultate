bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 7) [100 * (d + 3) - 10] / d
    
    d dw 10
    aux dd 0

; our code starts here
segment code use32 class=code
    start:
        
        mov ax, 3
        add ax, [d] ; ax = d + 3
        mov bx, 100 ; bx = 100
        mul bx ; dx:ax = 100 * (d + 3)
        mov word[aux + 2], dx
        mov word[aux + 0], ax ; aux = dx:ax = 100 * (d + 3)
        mov ebx, 10 ; ebx = 10
        mov ecx, [aux] ; ecx = aux = 100 * (d + 3)
        sub ecx, ebx ; ecx = ebx - ecx = 100 * (d + 3) - 10
        mov [aux], ecx ; aux = ecx = 100 * (d + 3) - 10
        mov dx, word[aux + 2]
        mov ax, word[aux + 0] ; dx:ax = aux = 100 * (d + 3) - 10
        div word[d] ; dx:ax / d => ax = cat, dx = rest
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
