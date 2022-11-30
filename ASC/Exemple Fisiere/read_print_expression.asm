;1. Read two numbers a, b in decimal. Read two numbers in hexadecimal (c and d).
;Compute the following expression: 12 / a + (c*d + b*1010b) / 12h and print the result on screen in hexadecimal and decimal.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit  , printf, scanf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          import printf msvcrt.dll
                          import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data


  a dd 0
  b dd 0
  c dd 0
  d dd 0
  formatdecimal db '%d', 0
  formathexadecimal db '%x',0
  printresult db 'result = %x in hexadecimal and %d in decimal', 0  ; de la drpata la st pe stiva: valoarea rez pentru %d si apoi valoarea rez petru %x
  printmesajinceputa db 'Introduceti valoarea pentru a in decimal =', 0
    printmesajinceputb db 'Introduceti valoarea pentru b in decimal =', 0
      printmesajinceputc db 'Introduceti valoarea pentru c in hexadecimal =', 0
        printmesajinceputd db 'Introduceti valoarea pentru d in hexadecimal =', 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        ;afisare mesaj inceput a
        
        push dword printmesajinceputa
        call [printf]
        add esp, 4*1
        ; citire a
        
         push dword a
         push dword formatdecimal
         call [scanf]
         add esp, 4*2
         
          ;afisare mesaj inceput b
        
        push dword printmesajinceputb
        call [printf]
        add esp, 4*1
        ; citire b
        
         push dword b
         push dword formatdecimal
         call [scanf]
         add esp, 4*2
         
         
          ;afisare mesaj inceput c
        
        push dword printmesajinceputc
        call [printf]
        add esp, 4*1
        
        ; citire c
        
         push dword c
         push dword formathexadecimal
         call [scanf]
         add esp, 4*2
         
          ;afisare mesaj inceput d
        
        push dword printmesajinceputd
        call [printf]
        add esp, 4*1
        ; citire d
        
         push dword d
         push dword formathexadecimal
         call [scanf]
         add esp, 4*2
         
         ; calcul expresie 12 / a + (c*d + b*1010b) / 12h
         ; (c*d + b*1010b) 
         mov eax, [c]
         imul dword [d]   ; edx:eax = c*d
         
         ; copie pt edx:eax in ecx:ebx
         
         mov ebx, eax
         mov ecx, edx
            ;  b*1010b
            
         mov eax, 1010b
         imul dword [b] ; edx:eax = 1010b*b
         
         ;c*d + b*1010b
         ; ecx:ebx + 
         ; edx:eax
         clc
         add eax, ebx
         adc edx, ecx  ; edx:eax = c*d + b*1010b
         
         ;(c*d + b*1010b ) / 12h
         mov ebx, 12h
         ; edx:eax = c*d + b*1010b
         idiv ebx   ; edx:eax/ ebx   = eax - catul imp si in edx restul imp, deci eax = (c*d + b*1010b) / 12h
         
         ; salvare eax in ebx
         mov ebx, eax; ebx = (c*d + b*1010b) / 12h
         
          ;12 / a
          mov eax, 12
          CDQ  ; eax -> edx:eax
          idiv dword [a]  ; eax - catul imp 12 / a si in edx restul
          
;     2 / a + (c*d + b*1010b) / 12h
        add eax, ebx ; eax = resultatul expresiei = 2 / a + (c*d + b*1010b) / 12h
        
        ; afisare rezultat
        
        ; printresult db 'result = %x in hexadecimal and %d in decimal', 0
        
        push eax  ; va inlocui %d
        push eax   ; va inlocui %x
        push dword printresult
        call [printf]
        add esp, 4*3
          
          
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
