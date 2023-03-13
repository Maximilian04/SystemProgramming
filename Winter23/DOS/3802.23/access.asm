.model tiny
.code
.286
locals @@

org 80h
ArgCount:       db ?
Args:           db ?

org 100h

; probox.com 8 21 3 2 F 19 C 1A 15 10 9 7 8 3 12
; probox.com 8 21 9 10 E 15 15 15 15 15 15 15 15 3 D E We Qqerreqwerq

Start:

                mov ax, 0b800h                  ; адрес сегмента с видеопамятью -> es
                mov es, ax                      ;
                mov ax, ss                      ; Segment with stack, code, etc.
                mov ds, ax                      ;

                call ScanPassword
                call CheckPassword

                test ax, ax
                jz ReturnProgram                ; >>>>>>>>>>>>>>
                
                mov bh, 0
                mov bl, byte ptr [boxTheme]
                mov ah, byte ptr [boxColor]

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

                mov si, offset TextOK
                call PrintText

ReturnProgram:                                  ; <<<<<<<<<<<<<<
                mov ax, 4c00h                   ; exit(0)
                int 21h



;------------------------------------------------
; Prints text into the box
;------------------------------------------------
; Entry:        None
;
; Expects:      DS:SI -> text
;
; Exit:         None
;
; Destroys:     AX BX CX DX SI DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     [bp + 2]
;               stored BP   [bp]
;               text ptr    [bp - 2]
;               ...
;------------------------------------------------

PrintText       proc
                push bp
                mov bp, sp                      ; Complete stack frame
                push si


                push es
                ; mov di, ds                      ; ds -> es
                ; mov es, di                      ;
                mov di, cs                      ; cs -> es
                mov es, di                      ;
                mov di, si                      ; si -> di
                call StrLen
                pop es                          ; restore es -> vidmem
                mov dx, cx                      ; dx = text length
                
                mov ch, byte ptr boxHeightPos
                add ch, 1d
                mov cl, byte ptr boxWidthPos
                add cl, 1d
                call CalculateVidMemPos

                mov cx, dx                      ; cx = text length
                mov dh, byte ptr boxHeight
                mov dl, byte ptr boxWidth

                cmp cl, dl
                jge @@OneChar                   ; >>====\\
                                                ;       ||
                mov dh, 0                       ;       ||
                sub dl, cl                      ;       ||
                shr dl, 1                       ; Center offset
                shl dl, 1                       ;       ||
                add bx, dx                      ;       ||
                jmp @@OneChar                   ; >>====\\
                                                ;       ||
                                                ; <<====//
    @@OneChar:                                  ; <-------------------------\
                test dh, dh                     ;                           |
                jz @@LastLine                   ; >>====\\                  |
                                                ;       ||                  |
                test dl, dl                     ;       ||                  |
                jnz @@noLineBreak               ;       ||                  |
                                                ;       ||                  |
                mov dl, byte ptr boxWidth       ;       ||                  |
                dec dh                          ;       ||                  |
                                                ;       ||                  |
                add bx, 160d                    ; Next Line                 |
                mov ah, 0                       ;       ||                  |
                mov al, dl                      ;       ||                  |
                shl ax, 1                       ;       ||                  |
                sub bx, ax                      ;       ||                  |
                                                ;       ||                  |
            @@noLineBreak:                      ;       ||                  |
                dec dl                          ;       ||                  |
                                                ;       ||                  |
            @@LastLine:                         ; <<====//                  |
                mov al, byte ptr [si]           ;                           |
                mov es:[bx], al                 ;                           |
                                                ;                           |
                inc si                          ;                           |
                inc bx                          ;                           |
                                                ;                           |
                mov al, byte ptr [boxTextColor] ;                           |
                mov es:[bx], al                 ;                           |
                inc bx                          ;                           |
                                                ;                           |
                loop @@OneChar                  ; >-------------------------/



                pop bp
                pop bp                          ; Stack frame
                ret
PrintText       endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Gets information from cmd argument
;------------------------------------------------
; Entry:        None
;
; Expects:      None
;
; Exit:         AX = 0 if no errors, 1 contrary
;               textFlag = 1 if DS:SI -> box text, 0 if no text
;
; Destroys:     BX CX SI DI (DH if error)
;------------------------------------------------
; Stack frame:
;               ...
;               textFlag    [bp + 4]
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
                test ax, ax
                jz @@ContinueHere5
                jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>
                @@ContinueHere5:

                mov bx, 0
                call MScnNHex
                mov byte ptr [boxTheme], bl

                mov cx, 02h
                cmp bx, cx
                jle @@Theme02                   ; ---->
                mov cx, 0Eh
                cmp bx, cx
                je @@ThemeE                     ; ---->
                mov cx, 0Fh
                cmp bx, cx
                je @@ThemeF                     ; ---->
                mov cx, 0C0h
                cmp bx, cx
                jge @@ThemeC                    ; ---->

                jmp @@SetErrorBadTheme
TextOK:         db "Access granted"
                db 090h

;    0,  1,  2 - standart box         & text
;   C0, C1, C2 - standart box & color & text
;   F       - various symbols & color & text
;   E       - various symbols & color & text & textColor

@@Theme02:                                      ; <----
                jmp @@LastArg                   ; ->>>>>>>>>>>>>

@@ThemeF:                                       ; <----
                mov byte ptr [boxTheme], 03d
@@ThemeE:                                       ; <----

                mov di, offset BoxAssetStart + 3
                mov cx, offset BoxAssetStep     ; cx = step
                sub cx, offset BoxAssetStart    ;

    @@OneStep:                                  ; <-------------------------\
                test ax, ax                     ;                           |
                jz @@ContinueHere6              ;                           |
                jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>            |>>>
                @@ContinueHere6:                ;                           |
                                                ;                           |
                mov bx, 0                       ;                           |
                call MScnNDec                   ;                           |
                mov [di], bl                    ;                           |
                                                ;                           |
                add di, cx                      ;                           |
                                                ;                           |
                mov bx, offset BoxAssetEnd      ;                           |
                cmp di, bx                      ;                           |
                jl @@OneStep                    ; >-------------------------/
                
                jmp @@SetColor                  ; >>====\\
                                                ;       ||
@@ThemeC:                                       ; <-----||--
                mov cx, 0C2h                    ;       ||
                cmp bx, cx                      ;       ||
                jng @@ContinueHere10            ;       ||
                jmp @@SetErrorBadTheme          ; >>>>>>||>>>>>>
                @@ContinueHere10:               ;       ||
                                                ;       ||
                sub byte ptr [boxTheme], 0C0h   ;       ||
                                                ;       ||
@@SetColor:                                     ; <<====//
                test ax, ax
                jz @@ContinueHere11
                jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>
                @@ContinueHere11:

                mov bx, 0
                call MScnNHex
                mov byte ptr [boxColor], bl
                mov byte ptr [boxTextColor], bl


                mov bh, 0
                mov bl, byte ptr [boxTheme]
                mov cx, 0Eh
                cmp bx, cx
                je @@ThemeEColor
                jmp @@LastArg                   ; ->>>>>>>>>>>>>
@@ThemeEColor:
                mov byte ptr [boxTheme], 03d

                test ax, ax
                jz @@ContinueHere12
                jmp @@SetErrorNoArg             ; >>>>>>>>>>>>>>
                @@ContinueHere12:

                mov bx, 0
                call MScnNHex
                mov byte ptr [boxTextColor], bl
                jmp @@LastArg                   ; ->>>>>>>>>>>>>


@@LastArg:                                      ; <<<<<<<<<<<<<-
                test ax, ax
                jz @@hasText                    ; >>====\\
                                                ;       ||
                mov word ptr ss:[bp + 4], 0     ;       ||
                                                ;       ||
                mov ax, 0                       ;       ||
                jmp @@ProcEnd                   ; >-\   ||
                @@hasText:                      ; <<|===//
    PasswordCode:                               ;   |
                mov word ptr ss:[bp + 4], 1     ;   |           ;!!! C746040100
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                ; db 07                                ;   |
                                                ;   |
                mov ax, 0                       ;   |
                jmp @@ProcEnd                   ; >-\
@@SetErrorNoArg:                                ; <<|<<<<<<<<<<<
                mov ax, 0239h                   ; Error code: No argument (more expected) : 239
                mov dh, 00Ch                    ;   |
                mov bx, 160d*4+3d*2             ;   |
                call PrintNHex                  ;   |
                mov ax, 0239h                   ;   |
                                                ;   |
                                                ;   |
                jmp @@ProcEnd                   ; >-\
@@SetErrorBadTheme:                             ; <<|<<<<<<<<<<<
                mov ax, 0240h                   ; Error code: No argument (more expected) : 240
                mov dh, 00Ch                    ;   |
                mov bx, 160d*4+3d*2             ;   |
                call PrintNHex                  ;   |
                mov ax, 0240h                   ;   |
                                                ;   |
                                                ;   |
@@ProcEnd:                                      ; <-/
                pop bp                          ; Stack frame
                ret
GetArgs         endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Scans the password
;------------------------------------------------
; Entry:        none
;
; Expects:      
;
; Exit:         
;
; Destroys:     AX CL Si
;------------------------------------------------
;------------------------------------------------
ScanPassword    proc

                mov di, offset PasswordBuffer

@@ScanDigit:                                    ; <-------------------------\
                                                ;                           |
                mov ah, 01h                     ; getc -> al                |
                int 21h                         ; ^                         |
                                                ;                           |
                cmp al, 13d                     ; Stop scan if enter        |
                je @@EndScanDigit               ; >>========================|=======\\
                                                ;                           |       ||
                mov byte ptr cs:[di], al        ;                           |       ||
                inc di                          ;                           |       ||
                                                ;                           |       ||
                ; mov cl, al                      ; Store al to cl            |       ||
                                                ;                           |       ||
                ; mov ax, bx                      ; bx *= 10                  |       ||
                ; mov si, 10d                     ; ^                         |       ||
                ; mul si                          ; ^                         |       ||
                ; mov bx, ax                      ; ^                         |       ||
                                                ;                           |       ||
                ; mov al, cl                      ; Retore al from cl         |       ||
                                                ;                           |       ||
                ; sub al, "0"                     ; ASCII "0" offset          |       ||
                                                ;                           |       ||
                ; mov ah, 0d                      ; bx += al                  |       ||
                ; add bx, ax                      ; ^                         |       ||
                                                ;                           |       ||
                jmp @@ScanDigit                 ; >-------------------------/       ||
                                                ;                                   ||
@@EndScanDigit:                                 ; <<================================//
                ret

ScanPassword    endp

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


;------------------------------------------------
; Count the length of the 0Dh-terminated string (str)
;------------------------------------------------
; Entry:        ES:DI = str
;
; Expects:      DF = 0 (CLD)
;
; Exit:         CX = length
;
; Destroys:     AL DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).

StrLen          proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame

                ; mov al, 00Dh                    ; AL = terminator
                mov al, 090h                    ; AL = terminator
                xor cx, cx                      ; CX = 0

@@CountStep:                                    ; <-------------------------\
                inc cx                          ;                           |
                scasb                           ;                           |
                jne @@CountStep                 ; >-------------------------/

                dec cx

                ; pop bp                          ; Stack frame
                ret
StrLen          endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Checks password correctness
;------------------------------------------------
; Entry:        None
;
; Expects:      cs:si -> password
;
; Exit:         AX = 1 if correct
;
; Destroys:     BX SI DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).
PasswordLength = 4                              ; C746
PasswordBufLength = 6

CheckPassword   proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame


                mov di, offset PasswordBuffer
                ; mov si, cs:[0239h]; ~~ 2E8B36 3902
                ; db 02Eh, 08Bh, 036h
; PasswordAddr:   dw offset PasswordTray

                ; mov si, 0239h; ~~ BE 3902
                db 0BEh
PasswordAddr:   dw offset PasswordTray


                mov cx, PasswordLength
                mov ax, 1
    @@Step:                                     ; <-------------------------\
                                                ;                           |
                                                ;                           |
                cmp byte ptr cs:[di], 090h      ;                           |
                je @@PasswordEnd                ; >---------\               |
                mov bl, byte ptr cs:[di]        ;            \              |
                cmp byte ptr cs:[si], bl        ;             \             |
                jne @@WrongPassword             ; >>====\\     \            |
                                                ;       ||      \           |
                inc di                          ;       ||       \          |
                inc si                          ;       ||        \         |
                loop @@Step                     ; >-----++---------\--------/
                                                ;       ||          \
                jmp @@PasswordEnd               ; >-----++----------->------\
            @@WrongPassword:                    ; <<====//                  |
                mov ax, 0                       ;                           |
                                                ;                           |
                jmp @@PasswordEnd               ; >-------------------------\
            PasswordBuffer:                     ;                           |
                db PasswordBufLength DUP(90h)   ;                           |
            PasswordTray:                       ;                           |
                db "Admin"                      ;                           |
                db (PasswordBufLength - 5) DUP(90h);                        |
            @@PasswordEnd:                      ; <-------------------------/

                ; pop bp                          ; Stack frame
                ret
CheckPassword   endp

;------------------------------------------------
;------------------------------------------------


include ..\LianLib\ScanNDec.asm
include ..\LianLib\PrntNBin.asm
include ..\LianLib\PrntNHex.asm
include ..\LianLib\PrntNDec.asm
include ..\LianLib\MScnNDec.asm
include ..\LianLib\MScnNHex.asm

include ..\LianLib\ProBox.asm
include ..\LianLib\DrawLine.asm

.data
include ..\LianLib\Alphabet.asm

boxHeightPos:   db 20
boxWidthPos:    db 30
boxHeight:      db 3
boxWidth:       db 20
boxTheme:       db 2
boxColor:       db 00Ah
boxTextColor:   db 00Ah

end             Start
