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
                mov ax, ss                      ; Segment with stack, code, etc.
                mov ds, ax                      ;

                call GetArgs
                mov bx, 0
                cmp ax, bx
                jne ReturnProgram

                mov dh, 01Ah
                mov ah, 0
                mov al, byte ptr [ArgCount]
                mov bx, 160d*17 + 160d/2 - 18d + 4d; Середина строчки
                call PrintNDec

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
                mov bx, 160d*18 + 160d/2 + 4d; Середина строчки
                call DrawBox
                add sp, 2*9d


                ; mov dh, 00000010b               ; Dark green on black
                ; pop ax                          ; Scanned number
                ; push ax                         ;

                ; call PrintNBin

ReturnProgram:
                mov ax, 4c00h                   ; exit(0)
                int 21h


;------------------------------------------------
; Gets information from cmd argument
;------------------------------------------------
; Entry:        None
;
; Expects:      None
;
; Exit:         AX = 0 if no errors, 1 contrary
;
; Destroys:     AX BX CX DX DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     [bp + 2]
;               stored BP   [bp]
;               ...
;------------------------------------------------

GetArgs         proc
                push bp
                mov bp, sp                      ; Complete stack frame


                mov ax, 2d                      ; At least one argument
                mov bh, 0                       ;
                mov bl, byte ptr [ArgCount]     ;
                cmp ax, bx                      ;
                jg @@SetError                   ;

                ; mov bh, 0                       ; 
                ; mov bl, byte ptr ArgCount       ;
                ; mov ax, 020h                    ;
                ; mov [offset Args + bx], ax      ;

                mov bx, 0
                mov si, offset Args + 1
                mov dl, 020h                    ; Terminator 20h
                mov dh, 00Dh                    ; Terminator 0Dh
                call MScnNDec

                mov ah, 0
                mov al, bl
                mov dh, 004h
                mov bx, 160d*4+7d*2
                call PrintNHex

                mov ax, 4d
                ; mov bh, 0
                ; mov bl, byte ptr [ArgCount]
                cmp ax, bx
                jg @@SetError
                jmp @@SetError

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

                mov ax, 0
                jmp @@ProcEnd                   ; >>\\
@@SetError:                                     ;   ||
                mov ah, 0                       ;   ||
                mov al, byte ptr [ArgCount]     ;   ||
                mov dh, 00Ch                    ;   ||
                mov bx, 160d*4+3d*2             ;   ||
                call PrintNHex                  ;   ||
                mov ax, 2                       ;   ||
                                                ;   ||
@@ProcEnd:                                      ; <<//
                pop bp                          ; Stack frame
                ret
GetArgs         endp

;------------------------------------------------
;------------------------------------------------


include ..\LianLib\ScanNDec.asm
include ..\LianLib\PrntNBin.asm
include ..\LianLib\PrntNHex.asm
include ..\LianLib\PrntNDec.asm
include ..\LianLib\MScnNDec.asm

include ..\LianLib\ProBox.asm
include ..\LianLib\DrawLine.asm

.data
include ..\LianLib\Alphabet.asm

boxHeightPos:   db ?
boxWidthPos:    db ?
boxHeight:      db ?
boxWidth:       db ?

end             Start
