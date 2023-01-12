bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
;Se da un sir de cuvinte. Sa se obtina din acesta un sir de dublucuvinte, in care fiecare dublucuvant va contine nibble-urile despachetate pe octet (fiecare cifra hexa va fi precedata de un 0), aranjate crescator in interiorul dublucuvantului. 
;pentru sirul initial:
;01732h, 8475h, 0ADBCh, ...
;Se va obtine:
;01020307h,  04060708h, 0A0D0B0Ch, ... 


segment code use32 class=code
start:
    push ebp
    mov ebp, esp
    mov ebp, [ebp]
    mov ebx, [ebp]
    mov [esp], ebx

	push dword 0 ; push the parameter for exit onto the stack
	call [exit] ; call exit to terminate the program