;------------------------------------------------
; Draws line on the screen (Pattern ABB~BBC)
;------------------------------------------------
; Entry:        DI = start addr to draw
;               CX = width of line (without A&C)
;
; Expects:      ES -> Video segment
;               DF = 0 (CLD)
;
; Exit:         None
;
; Destroys:     AX CX DI
;------------------------------------------------
; Stack frame:
;               ...
;               'A' char    [bp + 8]    // H - color attr
;               'B' char    [bp + 6]    // L - symb attr
;               'C' char    [bp + 4]    //
;               retAddr     [bp + 2]
;               stored BP   [bp]
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).

DrawLine        proc
                push bp
                mov bp, sp                      ; Complete stack frame

                mov ax, [bp + 8]
                stosw
                
                mov ax, [bp + 6]
                rep stosw
                
                mov ax, [bp + 4]
                stosw

                pop bp                          ; Stack frame
                ret
DrawLine        endp

;------------------------------------------------
;------------------------------------------------
