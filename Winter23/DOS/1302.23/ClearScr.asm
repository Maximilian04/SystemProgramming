.model tiny
.code
locals @@
org 100h

Start:
                mov ax, 0b800h                  ; адрес сегмента с видеопамятью
                mov es, ax                      ;

                mov bx, 160d*10 + 160d/2        ; Середина 5 строчки
                                                ; Каждой строчке соответствует 160 байт                

                mov cx, 2000d+160d*2d           ;
                mov bx, 0                       ;

                mov ax, 4efeh                   ; Yellow squere on Red
                mov bx, 0
                mov cx, 80d*25d                 ; Screen W*H
                call ClearScr

                mov ax, 4c00h                   ; exit(0)
                int 21h

;------------------------------------------------
; Clears the screen
;------------------------------------------------
; Entry:        AH = color attr for erasing
;               AL = symbol for erasing
;               BX = start addr to erase
;               CX = number of symbol to erase
;
; Expects:      ES -> Video segment
;
; Exit:         None
;
; Destroys:     BX CX
;------------------------------------------------

ClearScr        proc

@@EraseStep:                                    ; <------------------\
                mov es:[bx], ax                 ;                    |
                add bx, 2                       ;                    |
                                                ;                    |
                loop @@EraseStep                ; >------------------/

                ret
ClearScr        endp

;------------------------------------------------
                                                 
end             Start

