.model tiny
.code
locals @@
org 100h

Start:
                mov ax, 0b800h                  ; адрес сегмента с видеопамятью
                mov es, ax                      ;

                mov bx, 160d*10 + 160d/2        ; Середина строчки
                                                ; Каждой строчке соответствует 160 байт                

                mov bx, 0                       ;

                mov ah, 00001010b               ; Bright green
                mov bx, 160d*18+10d
                mov ch, 5                       ; Box H
                mov cl, 19                      ; Box W
                call DrawBox

                mov ax, 4c00h                   ; exit(0)
                int 21h

;------------------------------------------------
; Draws box on the screen
;------------------------------------------------
; Entry:        AH = color attr
;               BX = start addr to draw
;               CH = height of box
;               CL = width of box
;
; Expects:      ES -> Video segment
;
; Exit:         None
;
; Destroys:     AL BX
;------------------------------------------------

DrawBox         proc
                push cx                         ; Store cx to stack

                mov al, byte ptr [BoxSymbols]   ; "?" -> ax (colored)
                mov es:[bx], ax                 ;

                                                ;-------------------------------------------

                mov al, byte ptr [BoxSymbols+1] ; "?" -> ax (colored)
                mov ch, 0                       ; cx = width
                sub cx, 2d
@@UpLine:                                       ; <-----------------\
                add bx, 2                       ; b+=2 (Next char)  |
                mov es:[bx], ax                 ;                   |
                                                ;                   |
                loop @@UpLine                   ; >-----------------/

                                                ;-------------------------------------------

                mov al, byte ptr [BoxSymbols+2] ; "?" -> ax (colored)
                add bx, 2                       ; b+=2 (Next char)
                mov es:[bx], ax                 ;

                                                ;-------------------------------------------

                mov al, byte ptr [BoxSymbols+3] ; "?" -> ax (colored)
                pop cx
                push cx
                mov cl, ch
                mov ch, 0                       ; cx = height
                sub cx, 2d
@@RightLine:                                    ; <-----------------\
                add bx, 160d                    ; b+=160 (Next line)|
                mov es:[bx], ax                 ;                   |
                                                ;                   |
                loop @@RightLine                ; >-----------------/

                                                ;-------------------------------------------

                mov al, byte ptr [BoxSymbols+4] ; "?" -> ax (colored)
                add bx, 160d                    ; b+=160 (Next line)|
                mov es:[bx], ax                 ;

                                                ;-------------------------------------------

                mov al, byte ptr [BoxSymbols+1] ; "?" -> ax (colored)
                pop cx
                push cx
                mov ch, 0                       ; cx = width
                sub cx, 2d
@@BottomLine:                                   ; <-----------------\
                sub bx, 2                       ; b-=2 (Prev char)  |
                mov es:[bx], ax                 ;                   |
                                                ;                   |
                loop @@BottomLine               ; >-----------------/                

                                                ;-------------------------------------------

                mov al, byte ptr [BoxSymbols+5] ; "?" -> ax (colored)
                sub bx, 2                       ; b+=2 (Next char)
                mov es:[bx], ax                 ;

                                                ;-------------------------------------------

                mov al, byte ptr [BoxSymbols+3] ; "?" -> ax (colored)
                pop cx
                push cx
                mov cl, ch
                mov ch, 0                       ; cx = height
                sub cx, 2d
@@LeftLine:                                     ; <-----------------\
                sub bx, 160d                    ; b+=160 (Next line)|
                mov es:[bx], ax                 ;                   |
                                                ;                   |
                loop @@LeftLine                 ; >-----------------/

                                                ;-------------------------------------------

                pop cx                          ; Clear stack

                ret
DrawBox         endp

;------------------------------------------------
;------------------------------------------------

.data

BoxSymbols:     db 0c9h, 0cdh, 0bbh, 0bah, 0bch, 0c8h ; "??????"

end             Start
