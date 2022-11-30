bits 32
global start        
extern exit, printf, scanf  
import exit msvcrt.dll    
import printf msvcrt.dll   
import scanf msvcrt.dll     
                          
segment data use32 class=data
    a dd 0
    b dd 0
    result dd 0
    format1 db 'Introduceti a=', 0	; format este un sir C
    format2 db 'Introduceti b=', 0      
    readformat db '%d', 0  
    printformat db 'S-a citit a=%d + b=%d . Rezultatul sumei este = %d (rez)', 0  
    ; elem din printformat se pun pe stiva de la dreapta la stanga 
    mesajptcitire db 'introduceti datele: a= si b=', 0
    
    n dd 0
    m dd 0
    formatnoucitire db '%d %d', 0

segment code use32 class=code
start:
   ; apel printf(“Introduceti a=”)
    push dword format1
    call [printf]
    add esp, 4*1

    ; apel scanf(“%d”, a)
    push dword a		; se pune pe stiva offset-ul variabilei!!
    push dword readformat
    call [scanf]
    add esp, 4*2

    ; apel printf(“Introduceti b=”)
    push dword format2
    call [printf]
    add esp, 4*1
    
    

    ; apel scanf(“%d”, b)
    push dword b    	; se pune pe stiva offset-ul variabilei!!
    push dword readformat
    call [scanf]
    add esp, 4*2
    

    
   
    

    mov eax, [a]
    add eax, [b]
    mov [result], eax

    ; !!!! daca rez sunt de dim mai mica decat 32 biti inainte de a fi puse pe sitva pentru afisare trebuie sa fie convertite la doublewords.
    
    ; apel printf(mesajdeafisat, a, b, result)
    push dword [result]     ; pune pe stiva valoarea rezultatului 
    push dword [b]          ; pune pe stiva valoarea lui b
    push dword [a]          ; pune pe stiva valoarea lui a
    push dword printformat
    call [printf]
    add esp,4*4

    push dword 0
    call [exit]

