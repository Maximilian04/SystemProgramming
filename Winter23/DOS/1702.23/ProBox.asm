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
                ; mov di, 160d*18 + 160d/2 - 18d*2 + 4d; Середина строчки
                ; mov cx, 5                       ; Width
                ; push 002DAh
                ; push 002CDh
                ; push 002BAh
                ; call DrawLine
                ; pop ax
                ; pop ax
                ; pop ax

                mov ch, 5
                mov cl, 5
                mov ah, 00Ah                    ; Light green on black
                mov bx, 2
                mov al, byte ptr [BoxAssetLU + bx]
                push ax
                mov al, byte ptr [BoxAsset_U + bx]
                push ax
                mov al, byte ptr [BoxAssetRU + bx]
                push ax
                mov al, byte ptr [BoxAssetR_ + bx]
                push ax
                mov al, byte ptr [BoxAssetRB + bx]
                push ax
                mov al, byte ptr [BoxAsset_B + bx]
                push ax
                mov al, byte ptr [BoxAssetLB + bx]
                push ax
                mov al, byte ptr [BoxAssetL_ + bx]
                push ax
                mov al, byte ptr [BoxAssetFI + bx]
                push ax
                mov bx, 160d*18 + 160d/2 - 18d*2 + 4d; Середина строчки
                call DrawBox
                add sp, 2*9d


                ; mov dh, 00000010b               ; Dark green on black
                ; pop ax                          ; Scanned number
                ; push ax                         ;

                ; call PrintNBin

                mov ax, 4c00h                   ; exit(0)
                int 21h



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
; Destroys:     AX BX (CX) DI
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


;                 ; push cx                         ; Store cx to stack
;                 mov dx, cx                      ; Store cx to dx

;                 mov al, byte ptr [BoxSymbols]   ; "?" -> ax (colored)
;                 mov es:[bx], ax                 ;

;                                                 ;-------------------------------------------

;                 mov al, byte ptr [BoxSymbols+1] ; "?" -> ax (colored)
;                 mov ch, 0                       ; cx = width
;                 sub cx, 2d
; @@UpLine:                                       ; <-----------------\
;                 add bx, 2                       ; b+=2 (Next char)  |
;                 mov es:[bx], ax                 ;                   |
;                                                 ;                   |
;                 loop @@UpLine                   ; >-----------------/

;                                                 ;-------------------------------------------

;                 ; pop cx                          ; Clear stack
;                 mov cx, dx

                pop cx
                pop bp                          ; Stack frame
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
