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
                test ax, ax
                jz @@ContinueHere1
                jmp ReturnProgram               ; >>>>>>>>>>>>>>
                @@ContinueHere1:

                ; mov dh, 01Ah
                ; mov ah, 0
                ; mov al, byte ptr [ArgCount]
                ; mov bx, 160d*17 + 160d/2 - 18d + 4d; Середина строчки
                ; call PrintNDec
                
                mov bx, 2

                mov ah, 00Ah                    ; Light green on black
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
                mov ch, byte ptr [boxHeightPos]
                mov cl, byte ptr [boxWidthPos]
                call CalculateVidMemPos
                mov ch, byte ptr [boxHeight]
                mov cl, byte ptr [boxWidth]
                call DrawBox
                add sp, 2*9d


                ; mov dh, 00000010b               ; Dark green on black
                ; pop ax                          ; Scanned number
                ; push ax                         ;

                ; call PrintNBin

ReturnProgram:                                  ; <<<<<<<<<<<<<<
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
; Destroys:     BX SI (DH if error)
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


                mov ah, 0                       ; At least one argument!
                mov al, byte ptr [ArgCount]     ;
                mov bx, 2d                      ;
                cmp ax, bx                      ;
                jnl @@ContinueHere1             ;
                jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>
                @@ContinueHere1:                ;

                            ; ONE STEP:
                            ; arg -> bx
                            ; if the last 1 -> ax
                            ; DS:SI -> next
                mov dl, 020h                    ; 20h Terminator
                mov dh, 00Dh                    ; 0Dh TerminatorEnd
                mov si, offset Args + 1         ; First argument

                mov bx, 0
                call MScnNDec
                mov byte ptr [boxHeightPos], bl
                test ax, ax
                jz @@ContinueHere2
                jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>
                @@ContinueHere2:


                mov bx, 0
                call MScnNDec
                mov byte ptr [boxWidthPos], bl
                test ax, ax
                jz @@ContinueHere3
                jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>
                @@ContinueHere3:
                
                mov bx, 0
                call MScnNDec
                mov byte ptr [boxHeight], bl
                test ax, ax
                jz @@ContinueHere4
                jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>
                @@ContinueHere4:
                
                mov bx, 0
                call MScnNDec
                mov byte ptr [boxWidth], bl
                ; test ax, ax
                ; jz @@ContinueHere
                ; jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>
                ; @@ContinueHere:





                ; mov ah, 0
                ; mov al, bl
                ; mov dh, 004h
                ; mov bx, 160d*4+7d*2
                ; call PrintNHex


                mov ax, 0
                jmp @@ProcEnd                   ; >-\
@@SetErrorNoArg:                                ; <<|<<<<<<<<<<<
                mov ax, 0239h                   ; Error code: No argument (more expected) : 239
                mov dh, 00Ch                    ;   |
                mov bx, 160d*4+3d*2             ;   |
                call PrintNHex                  ;   |
                mov ax, 0239h                   ;   |
                                                ;   |
                                                ;   |
@@ProcEnd:                                      ; <-/
                pop bp                          ; Stack frame
                ret
GetArgs         endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Calculate video mem offset by position
;------------------------------------------------
; Entry:        CH = heightPosition
;               CL = widthPosition
;
; Expects:      None
;
; Exit:         BX = start addr to draw
;
; Destroys:     AX
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------

CalculateVidMemPos  proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame


                ; bx = 160d * ch + 2 * cl
                mov bh, 0
                mov bl, cl
                sal bx, 1
                
                mov ax, 160d
                mul ch
                add bx, ax

                ; mov ax, bx
                ; mov bx, 80d
                ; call PrintNDec
                

                ; pop bp                          ; Stack frame
                ret
CalculateVidMemPos  endp

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
