bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 12) (a * d + e) / [c + h / (c - b)]

    a db 10
    b db 5
    c db 6
    d db 8
    e dw 24
    h dw 40
    
; our code starts here
segment code use32 class=code
    start:
        
        mov al, [a] ; al = a
        mul byte[d] ; ax = al * d = a * d
        add ax, [e] ; ax = a * d + e
        mov bx, ax  ; bx = ax = a * d + e
        mov cl, [c] ; cl = c
        sub cl, [b] ; cl = c - b
        mov ax, [h] ; ax = h
        div cl ; ax / cl = h / (c - b) => al = cat, ah = rest
        add al, [c] ; al = c + h / (c - b)
        mov cl, al ; cl = al = c + h / (c - b)
        mov ax, bx ; ax = bx = a * d + e
        div cl ; ax / cl = (a * d + e) / [c + h / (c - b)] => al = cat, ah = rest
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
