;------------------------------------------------
; Draws cool box on the screen
;------------------------------------------------
; Entry:        BX = start addr to draw
;               CH = height of box (without frame)
;               CL = width of box (without frame)
;
; Expects:      ES -> Video segment
;
; Exit:         None
;
; Destroys:     AX BX (CX) DX DI
;------------------------------------------------
; Stack frame:
;               ...
;               LU char     [bp + 20]   // H - color attr
;               _U char     [bp + 18]   // L - symb attr
;               RU char     [bp + 16]   //
;               R_ char     [bp + 14]   //
;               RB char     [bp + 12]   //
;               _B char     [bp + 10]   //
;               LB char     [bp + 8]    //
;               L_ char     [bp + 6]    //
;               FI char     [bp + 4]    //
;               retAddr     [bp + 2]
;               stored BP   [bp]
;               stored CX   [bp - 2]    // size
;               ...
;------------------------------------------------

DrawBox         proc
                push bp
                mov bp, sp                      ; Complete stack frame
                push cx

                                                ;-------------------------------------------
                                                ; Upper line
                mov di, bx
                mov cx, [bp - 2]
                mov ch, 0
                push [bp + 20]
                push [bp + 18]
                push [bp + 16]
                call DrawLine
                add sp, 2*3d
                                                ;-------------------------------------------
                                                ; Middle line
                mov cx, [bp - 2]
                mov dh, 0
                mov dl, ch
@@MiddleStep:                                   ; <-----------------\
                                                ;                   |
                add bx, 160d                    ;                   |
                mov di, bx                      ;                   |
                mov cx, [bp - 2]                ;                   |
                mov ch, 0                       ;                   |
                push [bp + 6]                   ;                   |
                push [bp + 4]                   ;                   |
                push [bp + 14]                  ;                   |
                call DrawLine                   ;                   |
                add sp, 2*3d                    ;                   |
                dec dx                          ;                   |
                jnz @@MiddleStep                ; >-----------------/
                                                ;-------------------------------------------
                                                ; Bottom line
                add bx, 160d
                mov di, bx
                mov cx, [bp - 2]
                mov ch, 0
                push [bp + 8]
                push [bp + 10]
                push [bp + 12]
                call DrawLine
                add sp, 2*3d
                                                ;-------------------------------------------

                pop cx
                pop bp                          ; Stack frame
                ret
DrawBox         endp

;------------------------------------------------
;------------------------------------------------

; needs <include ?\LianLib\DrawLine.asm>
