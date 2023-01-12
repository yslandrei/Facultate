bits 32
global start  
      
extern exit, fread, fprintf, fopen, fclose               ; tell nasm that exit exists even if we 
import exit msvcrt.dll    
import fread msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

;9) Se da un fisier text. Sa se citeasca continutul fisierului, sa se determine caracterul special (diferit de litera) cu cea mai mare frecventa si sa se afiseze acel caracter, impreuna cu frecventa acestuia. Numele fisierului text este definit in segmentul de date 

                       
segment data use32 class=data
    scanFormat1 db '%d', 0
    printFormat1 db 'Caracterul special: %c | Frecventa: %d', 0
    printFormat2 db '%d', 0
    inputFile db "in.txt", 0
    outputFile db "out.txt", 0
    writeMode db "w", 0
    readMode db "r", 0
    newLine db 10, 0
    descInput dd -1
    descOutput dd -1
    
    
    maxLen equ 100
    s resb 101
    sLen dd 0
    freq resb 256
    letters db 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    lLen equ $ - letters
    maxFreq dd 0
    special dd ''
    
    
segment code use32 class=code
    start:
        ; eax = fopen(&inputFile, &readMode)
        push dword readMode
        push dword inputFile
        call [fopen]
        add esp, 4 * 2
        
        mov [descInput], eax
        cmp eax, 0
        je final
        
        ; eax = fopen(&outputFile, &writeMode)
        push dword writeMode
        push dword outputFile
        call [fopen]
        add esp, 4 * 2
        
        mov [descOutput], eax
        cmp eax, 0
        je final
        
        
        ; eax  = fread(&s, 1, maxLen, descInput)
        push dword [descInput]
        push dword maxLen
        push dword 1 ; sizeof
        push dword s
        call [fread]
        add esp, 4 * 4
        
        mov [sLen], eax
        mov ecx, [sLen]
        mov esi, s
        
        repeat1:
            lodsb
            mov ah, al
            
            push ecx
            push esi
            mov ecx, lLen
            mov esi, letters
                
            checkLetter:
                lodsb
                cmp ah, al
                je isLetter
            loop checkLetter
            
            isNotLetter:
                pop esi
                pop ecx
                
                ; freq[ [esi] ] ++
                movzx ebx, byte[esi]
                inc byte[ebx + freq]
                
                ; maxFreq / special
                movzx ebx, byte[ebx + freq]
                cmp ebx, [maxFreq]
                jl endIf1
                mov [maxFreq], ebx            
                mov ebx, [esi]
                mov [special], ebx
                jmp endIf1
            
            isLetter:
                pop esi
                pop ecx
            endIf1:
        loop repeat1
        
        ; fprintf(descOutput, &printFormat1, special, maxFreq)
        push dword [maxFreq]
        push dword [special]
        push dword printFormat1
        push dword [descOutput]
        call [fprintf]
        add esp, 4 * 4
        
        ; fclose(descInput)
        push dword [descInput]
        call [fclose]
        add esp, 4 * 1
        
        
        ; fclose(descOutput)
        push dword [descOutput]
        call [fclose]
        add esp, 4 * 1
    
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
