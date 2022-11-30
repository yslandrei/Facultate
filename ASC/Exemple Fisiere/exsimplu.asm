bits 32
global start        
extern exit, printf, scanf  
import exit msvcrt.dll    
import printf msvcrt.dll   
import scanf msvcrt.dll     
                          
segment data use32 class=data
    a db 0
    b db 0
    result db 0
    format1 db 'a=', 0	; format este un sir C
    format2 db 'b=', 0      
    readformat db '%d', 0  
    printformat db '%d + %d = %d', 0  

segment code use32 class=code
start:
    ; apel printf(“a=”)
    push dword format1
    call [printf]
    add esp, 4*1

    ; apel scanf(“%d”, a)
    push dword a		; se pune pe stiva offset-ul variabilei!!
    push dword readformat
    call [scanf]
    add esp, 4*2

    ; apel printf(“b=”)
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

    ; apel printf(“%d + %d = %d\n”, a, b, result)
    push dword [result]     ; pune pe stiva valoarea rezultatului 
    push dword [b]          ; pune pe stiva valoarea lui b
    push dword [a]          ; pune pe stiva valoarea lui a
    push dword printformat
    call [printf]
    add esp, 4*4

    push dword 0
    call [exit]
