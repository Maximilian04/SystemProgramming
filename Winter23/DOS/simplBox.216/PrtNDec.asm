.model tiny
.code
locals @@
org 100h

Start:
                mov ax, 0b800h                  ; адрес сегмента с видеопамятью -> es
                mov es, ax                      ;

                mov si, 0h

                mov bx, 160d*19 + 160d/2        ; Середина 10 строчки
                                                ; Каждой строчке соответствует 160 байт

                mov dh, 00000010b               ; Dark green on black

                mov ax, 5F7Ch                   ; Print 1
                mov ax, 228d                    ; Print 1

                call PrintNDec

                mov ax, 4c00h                   ; exit(0)
                int 21h

;------------------------------------------------
; Prints number as decimal to vidmem
;------------------------------------------------
; Entry:        AX = number to print
;               BX = start addr to print
;
; Expects:      ES -> Video segment
;               DH = color code
;
; Exit:         None
;
; Destroys:     AX BX CX DL Si
;------------------------------------------------
;------------------------------------------------
PrintNDec       proc

                mov cx, 5d                      ; 5 digits in 2 byte in ax

@@PrintDigit:                                   ; <-------------------------\
                mov ch, dh                      ; Store dh to ch            |
                                                ;                           |
                mov dx, 0d                      ; for division              |
                mov si, 10d                     ; ax/10 -> ax &             |
                div si                          ; & ax%10 -> dx             | !!! dx < 10
                                                ;                           |
                mov si, dx                      ; dl -> si                  |
                                                ;                           |
                mov dl, byte ptr [Alphabet]+si  ; ASCII "0" offset          |
                                                ;                           |
                mov dh, ch                      ; Restore dh from ch        |
                mov ch, 0                       ; ^                         |
                                                ;                           |
                mov word ptr es:[bx], dx        ; Print dl on position bx   |
                                                ;                           |
                dec bx                          ; Next digit                |
                dec bx                          ; ^                         |
                                                ;                           |
                                                ;                           |
                loop @@PrintDigit               ; >-------------------------/

                ret

PrintNDec       endp

;------------------------------------------------
;------------------------------------------------

.data
Alphabet:       db "0123456789ABCDEF"           ; Alphabet for printing (Thanks Ilya)

end             Start
