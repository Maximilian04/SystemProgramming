.model tiny
.code
locals @@

org 80h
ArgCount:       db ?
Args:           db ?

org 100h

Start:

                mov ax, 0b800h                  ; адрес сегмента с видеопамятью -> es
                mov es, ax                      ;

                ; mov ax, ss                      ; Segment with stack, code, etc.
                ; mov ds, ax                      ;

                ; mov ah, 00001010b               ; Light green on black
                ; mov bx, 160d*18 + 160d/2 - 18d*2 + 4d; Середина строчки
                ; mov ch, 5                       ; Height
                ; mov cl, 18                      ; Width
                ; call DrawBox
                mov di, 160d*18 + 160d/2 - 18d*2 + 4d; Середина строчки
                mov cx, 5                       ; Width
                push 002DAh
                push 002CDh
                push 002BAh
                call DrawLine
                pop ax
                pop ax
                pop ax


                ; mov dh, 00000010b               ; Dark green on black
                ; pop ax                          ; Scanned number
                ; push ax                         ;

                ; call PrintNBin

                mov ax, 4c00h                   ; exit(0)
                int 21h





;------------------------------------------------
; Draws cool box on the screen
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

include ..\LianLib\ScanNDec.asm
include ..\LianLib\PrntNBin.asm
include ..\LianLib\PrntNHex.asm
include ..\LianLib\PrntNDec.asm

include ..\LianLib\DrawLine.asm

.data
include ..\LianLib\Alphabet.asm

end             Start
