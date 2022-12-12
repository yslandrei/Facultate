bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
                          
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;9.1) Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze: (a+b) / (a-b). Catul impartirii se va salva in memorie in variabila "rezultat" (definita in segmentul de date). Valorile se considera cu semn.

    a dd -1
    b dd -1
    rezultat dd -1
    printFormat1 db 'a = ', 0
    printFormat2 db 'b = ', 0
    scanFormat1 db '%d', 0
    printFormat3 db '(%d + %d) / (%d - %d)= %d', 0
    
    testt db 'a = %d, b = %d', 0
    
; our code starts here
segment code use32 class=code
    start:
        ; printf(“a = ”)
        push dword printFormat1
        call [printf]
        add esp, 4*1

        ; scanf(“%d”, &a)
        push dword a		; se pune pe stiva offset-ul variabilei!!
        push dword scanFormat1
        call [scanf]
        add esp, 4*2

        ; printf(“b = ”)
        push dword printFormat2
        call [printf]
        add esp, 4*1

        ; scanf(“%d”, &b)
        push dword b    	; se pune pe stiva offset-ul variabilei!!
        push dword scanFormat1
        call [scanf]
        add esp, 4*2
        
        mov eax, [a]
        add eax, [b] 
        mov edx, 0 ; edx:eax = a + b
        mov ecx, [a]
        sub ecx, [b] ; ecx = a - b
        idiv ecx ; edx:eax / ecx = eax(rest edx)
        mov [rezultat], eax
        
        ;printf("(%d + %d) / (%d - %d)= %d", a, b, a, b, rezultat)
        push dword[rezultat]
        push dword[b]
        push dword[a]
        push dword[b]
        push dword[a]
        push dword printFormat3
        call [printf]
        add esp, 4 * 6
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
