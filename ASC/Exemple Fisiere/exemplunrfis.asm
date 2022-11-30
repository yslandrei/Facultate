; sa se citeasca 2 numere  a si b din fisier1.txt. 
; Sa se afiseze in fisierul 2 rezultatul operatiei a/b in fisier2.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          
extern exit, fopen, fprintf, fclose, fscanf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll


; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

     fisier1 db "decitit.txt", 0   ; filename to be created
     fisier2 db "deafisat.txt",0
    access_mode2 db "w", 0       ; file access mode:
     access_mode1 db "r", 0       ; file access mode:
                                ; w - creates an empty file for writing ; r - for reading
    descriptor1 dd -1       ; variable to hold the file descriptor for fisier1
    descriptor2 dd -1       ; ; variable to hold the file descriptor for fisier2
    text db "text de afisat extra", 0  ; text to be write to file
    a dd 0
    b dd 0
    cat dd 0
    restul dd 0
   format_citire db '%d', 0
    format_mesaj_afisare db ' Cele doua numere citite sunt a= %d si b=%d', 0
   format_mesaj_afisare2 db ' Rezultatul operatiei %d / %d este: catul = %d si restul = %d', 0
   linie_noua db 10, 0
    

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ; call fopen() to open the file for reading
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode1    
        push dword fisier1
        call [fopen]
        add esp, 4*2                ; clean-up the stack
        mov [descriptor1], eax  ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final
        
        ; daca a reusit citirea:
        ;citire din fiser1 folosind fscanf        
        ; citire primul nr a din fisier
        push dword a
        push dword format_citire
        push dword [descriptor1]
        call [fscanf]
        add esp, 4*3
        
        ; citire al doilea nr din fisier: b
        push dword b 
        push dword format_citire
        push dword [descriptor1]
        call [fscanf]
        add esp, 4*3
        
        ; call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode2   
        push dword fisier2
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [descriptor2], eax  ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final
        
        ;daca e totul ok, efectuam calculele
        mov eax, [a]
        cdq 
        idiv dword[b] 
        mov [cat], eax
        mov [restul], edx
        
        
        ;afisare mesaj in fisier2
        
        push dword [b]
        push dword [a]
        push dword format_mesaj_afisare
        push dword [descriptor2]
        call [fprintf]
        add esp, 4*4

        ;trecere pe linie noua
         
        push dword linie_noua
        push dword [descriptor2]
        call [fprintf]
        add esp, 4*2
        

       ; write the text to file using fprintf()
        ; fprintf(file_descriptor, text)
       ; format_mesaj_afisare2 db ' Rezultatul operatiei %d / %d este: catul = %d si restul = %d', 0
        push dword [restul]
        push dword [cat]
        push dword [b]
        push dword [a]
        push dword format_mesaj_afisare2
        push dword [descriptor2]
        call [fprintf]
        add esp, 4*6

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [descriptor2]
        call [fclose]
        add esp, 4*1
        
         push dword [descriptor1]
        call [fclose]
        add esp, 4


      final:

    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

