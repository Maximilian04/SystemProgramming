.model tiny
.code
locals @@
org 100h

Start:
                mov ax, 0b800h                  ; адрес сегмента с видеопамятью -> es
                mov es, ax                      ;

                mov bx, 160d*19 + 160d/2        ; Середина 10 строчки
                                                ; Каждой строчке соответствует 160 байт

                mov dh, 00000010b               ; Dark green on black

                mov ax, 228d                    ; Print 1

                call PrintNBin

                mov ax, 4c00h                   ; exit(0)
                int 21h

;------------------------------------------------
; Clears the screen
;------------------------------------------------
; Entry:        AX = number to print
;               BX = start addr to print
;
; Expects:      ES -> Video segment
;               DH = color code
;
; Exit:         None
;
; Destroys:     BX CX
;------------------------------------------------
;------------------------------------------------
PrintNBin       proc

                mov cx, 16h                     ; 16 bit in 2 byte in ax

@@PrintDigit:                                   ; <-------------------------\
                push bx                         ; Store bx in stack         |
                                                ;                           |
                                                ;                           |
                mov dl, 00000001b               ; Mask                      |
                and dl, al                      ;                           |
                mov bl, 30h                     ; ASCII "0" offset          |
                add dl, bl                      ; ^                         |
                                                ;                           |
                                                ;                           |
                pop bx                          ; Restore bx from stack     |
                mov word ptr es:[bx], dx        ; Print dl on position bx   |
                                                ;                           |
                dec bx                          ; Next digit                |
                dec bx                          ; ^                         |
                                                ;                           |
                shr ax, 1d                      ; ax >> 1                   |
                                                ;                           |
                loop @@PrintDigit               ; >-------------------------/

                ret

PrintNBin       endp

;------------------------------------------------
;------------------------------------------------
                                                 
end             Start

