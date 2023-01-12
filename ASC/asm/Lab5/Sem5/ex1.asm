bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fread, fopen, fclose, fprintf          ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll  
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
; se citeste de la tastatura un numar n in baza 16 repr pe un word
; sa se deschide "in.txt" care contine exact 16 octeti
; si sa se afiseze pe ecran ac
n dd 0
formatr db "%x", 0
input db "in.txt", 0
read db "r", 0
des dd 0
char db 0
formatp db "%c", 0
; our code starts here
segment code use32 class=code
    start:
        push dword n
        push dword formatr
        call [scanf]
        add esp, 4 * 2
        push dword 
        push dword 
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
