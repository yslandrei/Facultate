     
   ; 2. Read numbers (in base 10) until the value 0 is read from the keyboard. 
;Compute and display the number of the inserted values and the sum of these values.
;Eg: 1, 3, 4, 0 => 3 values and sum = 8 

bits 32 ; assembling for the 32 bits architecture
global start        
extern exit  , printf, scanf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
 

 ;variabila x in caRE VOM RETINE NR CITITE
 x dd 0
 formatcitire db '%d', 0
 mesajafisare db ' S-au citit %d numere si suma lor este %d', 0
 suma dd 0
 inceput db 'Introduceti nr. Cand va opriti introduceti 0: ', 0
segment code use32 class=code
    start:
        mov ebx, 0 ; pt a count cifrele
        ;afisare mesaj inceput pe ecran
        push dword inceput
        call [printf]
        add esp, 4*1
        repeta:
            ;citire o val pentru x
            push dword x
            push dword formatcitire
            call [scanf]
            add esp, 4*2
            
            ;adunam la suma si incrememntam nr de val citite
            
            mov eax, [x]
            add [suma], eax
            inc ebx
            
            ; verificam daca s-a introdus 0 de la tastatura
            cmp eax, 0 
            JE finalsiafisare
            JNE repeta
            
            finalsiafisare:
                dec ebx   ; pentru ca il contorizeaza si pe 0
                ; S-au citit %d numere si suma lor este %d', 0
                push dword [suma]
                push ebx
                push dword mesajafisare
                call [printf]
                add esp, 4*3
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
