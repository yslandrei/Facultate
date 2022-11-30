   ; se citeste un caracter c si se citeste un sir s
    ; sa se afiseze pe ecran nr de apaitii al carcaterului citit c in sirul s

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          extern exit  , printf, scanf   , gets          ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          import printf msvcrt.dll
                          import scanf msvcrt.dll
                           import gets msvcrt.dll
segment data use32 class=data
    ; ...
 
    
s resb 20
format_sir db '%s', 0
mesaj db 'S-a citit acest sir:', 0 
formatcaracter db '%c', 0
caracter dd 0
mesajcitirec db 'introduceti un caracter: ', 0
mesajresultat db ' Caracterul %c apare de %d', 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
       ; a
        ;ana are mere 
        ; a de 3 ori
;citire        
push dword s
call [gets]
add esp, 4*1
                
;print pe ecran mesajul
        
push dword mesaj
call [printf]
add esp, 4*1
                
; print pe ecran sirul citit
     
push dword s
push dword format_sir        
call [printf]
add esp, 4*2

; afisare mesaj pt citire caracter
push dword mesajcitirec
call [printf]
add esp, 4*1

; citire carcaterului
    push dword caracter
    push dword formatcaracter
    call [scanf]
    add esp, 4*2
    
    ; determinare nr de aparitii a lui c in s
    
    mov ecx, 20 ; nr max de car pe care le putem avea in s
    mov esi, 0 ; pentru a parcurge sirul s
    
    mov ebx, 0 ; pentru a numara de cate ori apare c in s
    
    repeta:
        mov al, [s+esi] ; accesare elem din sir
        cmp al, [caracter]
        JE aduna
        JNE mergimaideparte
            aduna:
                inc ebx
                inc esi
            jmp end_repeta
            mergimaideparte:
                inc esi
                
                end_repeta:
    loop repeta
    ; afisare 
    ; mesajresultat db ' Caracterul %c apare de %d', 0
    push ebx
    push dword [caracter]
    push dword mesajresultat
    call [printf],
    add esp, 4*3
    
    


        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
