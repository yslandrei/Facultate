bits 32

global start    
    
extern exit, scanf, printf

import exit msvcrt.dll   
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
  
numar dd 0
format db '%x', 0
format2 db '%x ', 0
   
segment code use32 class=code
    start:
        
        repeta:
            
            push dword numar
            push dword format
            call [scanf]
            add esp, 4 * 2
            
            mov ebx, [numar]
            cmp ebx, -1
            je afara
 
            
            cmp ebx, 0FFFFFFh
            ja patruBytes
            
            cmp ebx, 0FFFFh
            ja treiBytes
            
            cmp ebx, 0FFh
            ja doiBytes
            
            jmp unByte
                       
            done:
            
            mov dl, 0FFh ; minim
            parcurge:
                cmp bl, dl
                jnb noMax
                    mov dl, bl
                noMax:
                shr ebx, 8
            loop parcurge
            
            movzx edx, dl
            push dword edx
            push dword format2
            call [printf]
            add esp, 4 * 2
            
        jmp repeta
        afara:
        
        jmp final
            
            patruBytes:
                mov ecx, 4
                jmp done
                
            treiBytes:
                mov ecx, 3
                jmp done
                
            doiBytes:
                mov ecx, 2
                jmp done
                
            unByte:
                mov ecx, 1
                jmp done
        
        final:

        push    dword 0  
        call    [exit]    
