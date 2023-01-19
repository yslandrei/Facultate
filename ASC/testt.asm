bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fprintf, fopen, printf, scanf, fscanf      ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll     
import printf msvcrt.dll
import scanf msvcrt.dll
import fscanf msvcrt.dll                    ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
n dd 0
cuvinte times 100 dd 0
format db "%s", 0
format_numar db "%d", 0
mesaj_error db "fisierul nu poate fi accesat", 0

sir times 100 db 0
len_sir times 100 db 0 

mod_acces db "w", 0
nume_fisier db "fisiertxtasm.txt.txt", 0
descriptor_fisier db 0
;sa se citeasca de la tastatura numarul n, apoi mai multe cuvinte pana cand se citeste cuvantul/caracterul "#". Sa se scrie intr-un fisier txt toate cuvintele citite care au cel putin n vocale
segment code use32 class=code

    start:
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp, 4*2
    
    mov [descriptor_fisier], eax
    cmp eax, 0
    je mesaj_eroare
    
    push dword n
    push dword format_numar
    call [scanf]
    add esp, 4*2     ;se citeste de la tastatura numarul n
    
    mov esi, 0
    
    mov ebx, 0
    repeta:
        push dword cuvinte
        push dword format
        call [scanf]
        add esp, 4*2   ;se citesc de la tastatura cuvinte
        
        
        
        mov esi, cuvinte
        
        
        
        vocala:
        inc ebx
        cmp ebx, [n]
        jne repeta
        
        
        scrie_in_fisier:
        push dword cuvinte
        push dword format
        push dword [descriptor_fisier]
        call [fscanf]
    jmp repeta
    
    
    
    
    mesaj_eroare:
    push dword mesaj_error
    call [scanf]
    add esi, 4
    
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program