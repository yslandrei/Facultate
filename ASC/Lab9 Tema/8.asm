bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; 8) Se da un sir de dublucuvinte. Sa se obtina sirul format din octetii inferiori ai
    ;    cuvintelor superioare din elementele sirului de dublucuvinte care sunt palindrom in scrierea in baza 10.
    
    s dd 4995CDD1h, 12345678h, 79h, 0Fh, 96B535h, 1h, 75BC371h ; => d db 95, 00, 96, 00, 5B
   ;s dd 1234554321, 305419896, 121, 15, 9876789, 1, 123454321
    ls equ ($ - s) / 4
    
    dbg1 db -1
    d resb ls
    dbg2 db -1
    
    restul dd 0
    zece dd 10

; our code starts here
segment code use32 class=code
    start:     
        mov ecx, ls
        mov esi, s
        mov edi, d
        
        repeat1:
            lodsd ; eax = current
            mov ebp, eax ; copia pt cmp final
            mov esp, eax ; copia
            mov ebx, 0 ; palindromul
            
            palindrom:
                ;esp = esp / 10
                mov eax, esp
                mov edx, 0 ; punem numarul pe qword pentru a realiza impartirea la 10. daca puneam doar pe
                           ; dword, catul ar fii dat overflow (ex: 1234554321/ 10 = 123455432 rest 1)
                div dword[zece] ; edx:eax / 10 = eax(rest edx)
                mov [restul], edx
                mov esp, eax
                
                ;ebx = ebx * 10
                mov eax, ebx
                mul dword[zece] ; eax * 10 = edx:eax (edx va fi mereu 0, conteaza eax)
                mov ebx, eax
                
                ;ebx = ebx + rest
                add ebx, [restul]   
            cmp esp, 0
            jne palindrom
            
            cmp ebx, ebp
            jne endif1
                ; octetii inferiori ai cuvintelor superioare
                ; adica acestia: 0011 0000h 
                shr ebx, 16
                mov al, bl
                stosb
            endif1:
            
        loop repeat1
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
