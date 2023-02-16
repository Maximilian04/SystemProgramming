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

                mov ax, 228d                    ; Print 1
                mov ax, 5F7Ch                   ; Print 1

                call PrintNHex

                mov ax, 4c00h                   ; exit(0)
                int 21h

;------------------------------------------------
; Prints number as hexagen to vidmem
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
PrintNHex       proc

                mov cx, 4d                      ; 4 digits in 2 byte in ax

@@PrintDigit:                                   ; <-------------------------\
                                                ;                           |
                mov dl, 00001111b               ; Mask                      |
                and dl, al                      ;                           |
                                                ;                           |
                mov si, dx                      ; dl -> si                  |
                and si, 0Fh                     ;                           |
                                                ;                           |
                mov dl, byte ptr [Alphabet]+si  ; ASCII "0" offset          |
                                                ;                           |
                mov word ptr es:[bx], dx        ; Print dl on position bx   |
                                                ;                           |
                dec bx                          ; Next digit                |
                dec bx                          ; ^                         |
                                                ;                           |
                shr ax, 4d                      ; ax >> 4                   |
                                                ;                           |
                loop @@PrintDigit               ; >-------------------------/

                ret

PrintNHex       endp

;------------------------------------------------
;------------------------------------------------

.data
Alphabet:       db "0123456789ABCDEF"           ; Alphabet for printing (Thanks Ilya)

end             Start
