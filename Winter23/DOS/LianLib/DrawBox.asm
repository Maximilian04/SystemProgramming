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
; Destroys:     AL BX DX
;------------------------------------------------

DrawBox         proc
                ; push cx                         ; Store cx to stack
                mov dx, cx                      ; Store cx to dx

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
                ; pop cx
                ; push cx
                mov cx, dx
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
                ; pop cx
                ; push cx
                mov cx, dx
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
                ; pop cx
                ; push cx
                mov cx, dx
                mov cl, ch
                mov ch, 0                       ; cx = height
                sub cx, 2d
@@LeftLine:                                     ; <-----------------\
                sub bx, 160d                    ; b+=160 (Next line)|
                mov es:[bx], ax                 ;                   |
                                                ;                   |
                loop @@LeftLine                 ; >-----------------/

                                                ;-------------------------------------------

                ; pop cx                          ; Clear stack
                mov cx, dx

                ret
DrawBox         endp

;------------------------------------------------
;------------------------------------------------
