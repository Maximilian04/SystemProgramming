.model tiny
.code
.286
locals @@
org 100h

boxWidth  = 10d
boxHeight = 13d
boxTheme  = 2
boxColor  = 00Eh

Start:          jmp Main
                ; mov ax, word ptr ss:[bx]     ~~ 368B 07
                ; mov ax, word ptr ss:[bx + 2] ~~ 368B 4702
                ; mov ax, word ptr ss:[bx + 4] ~~ 368B 4704
                ; mov ax, word ptr cs:[Ptr1]  ~~ 2E A1 2F01
                ;   Ptr1 = 012F
                ; mov word ptr cs:[Ptr1], ax ~~ 2E A3 2F01
                ; mov word ptr cs:[Ptr1], bx ~~ 2E 89 1E 2F01
                ; mov word ptr cs:[Ptr1], cx ~~ 2E 89 0E 2F01
                ; mov word ptr cs:[Ptr1], dx ~~ 2E 89 16 2F01
                ; mov word ptr cs:[Ptr1], si ~~ 2E 89 36 2F01
                ; mov word ptr cs:[Ptr1], di ~~ 2E 89 3E 2F01
                ; mov word ptr cs:[Ptr1], bp ~~ 2E 89 2E 2F01
                ; mov word ptr cs:[Ptr1], sp ~~ 2E 89 26 2F01
                ; mov word ptr cs:[Ptr1], ds ~~ 2E 8C 1E 2F01
                ; mov word ptr cs:[Ptr1], es ~~ 2E 8C 06 2F01
                ; mov word ptr cs:[Ptr1], ss ~~ 2E 8C 16 2F01
Ptr1:           db 90h
                db 90h
                ; mov ax, 239h                ~~ B8 39 02
                ; mov bx, 349h                ~~ BB 49 03

;------------------------------------------------
; Keyboard intterupt handler
;------------------------------------------------
;
;   Catches control keys & sets (State) variable
;
;------------------------------------------------

New09Int        proc
                push ax                 ; Stored regs
                ; mov ax, cs
                ; mov ds, ax

                in al, 60h              ; Catch key code

                cmp al, 01Dh            ; ctrl is pressed
                je @@ControlKey1
                cmp al, 09Dh            ; ctrl is released
                je @@ControlKey2

                jmp @@NotControlKey
            @@ControlKey1:
                                        ; Invert State variable
                xor byte ptr cs:[State], 01b

                jmp @@NotControlKey
            @@ControlKey2:
                                        ; Invert State variable

                jmp @@NotControlKey
            @@NotControlKey:

                in al, 61h              ; Set interruptor free
                or al, 80h
                out 61h, al
                and al, not 80h
                out 61h, al

                mov al, 20h             ; Set interruptor free
                out 20h, al


                pop ax                  ; Stored regs
                pushf
                db 09Ah                 ; CALL FAR
Old09Ofs        dw 0                    ; call old 09 interruption
Old09Seg        dw 0

                iret
                endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Timer intterupt handler
;------------------------------------------------
;
;   Draws
;
;------------------------------------------------

New08Int        proc
                push ax bx cx dx ds es si di    ; Stored regs

                ; mov word ptr cs:[Ptr1], ax ~~ 2E A3 2F01
                dw 0A32Eh
                dw offset RegAX
                ; mov word ptr cs:[Ptr1], bx ~~ 2E 89 1E 2F01
                dw 0892Eh
                db 01Eh
                dw offset RegBX
                ; mov word ptr cs:[Ptr1], cx ~~ 2E 89 0E 2F01
                dw 0892Eh
                db 00Eh
                dw offset RegCX
                ; mov word ptr cs:[Ptr1], dx ~~ 2E 89 16 2F01
                dw 0892Eh
                db 016h
                dw offset RegDX
                ; mov word ptr cs:[Ptr1], si ~~ 2E 89 36 2F01
                dw 0892Eh
                db 036h
                dw offset RegSI
                ; mov word ptr cs:[Ptr1], di ~~ 2E 89 3E 2F01
                dw 0892Eh
                db 03Eh
                dw offset RegDI
                ; mov word ptr cs:[Ptr1], bp ~~ 2E 89 2E 2F01
                dw 0892Eh
                db 02Eh
                dw offset RegBP
                ; mov word ptr cs:[Ptr1], sp ~~ 2E 89 26 2F01
                dw 0892Eh
                db 026h
                dw offset RegSP
                ; mov word ptr cs:[Ptr1], ds ~~ 2E 8C 1E 2F01
                dw 08C2Eh
                db 01Eh
                dw offset RegDS
                ; mov word ptr cs:[Ptr1], es ~~ 2E 8C 06 2F01
                dw 08C2Eh
                db 006h
                dw offset RegES
                ; mov word ptr cs:[Ptr1], ss ~~ 2E 8C 16 2F01
                dw 08C2Eh
                db 016h
                dw offset RegSS

                mov bx, sp

                mov ax, word ptr ss:[bx + 2]
                ; mov word ptr cs:[Ptr1], ax ~~ 2E A3 2F01
                dw 0A32Eh
                dw offset RegCS
                mov ax, word ptr ss:[bx + 0]
                ; mov word ptr cs:[Ptr1], ax ~~ 2E A3 2F01
                dw 0A32Eh
                dw offset RegIP

                mov bx, 0b800h                  ; ES -> vidmem segment
                mov es, bx
                mov bx, cs                      ; DS -> datasegment
                mov ds, bx


                ; mov al, byte ptr [State]
                ; mov byte ptr es:[bx], al


                ; push ds

                ; sub bx, 2d
                ; mov ah, 0d
                ; call PrintNHex

                test byte ptr cs:[State], 01b
                jz @@DoNotDraw                  ; >-----------------\
                test byte ptr [State], 10b      ;                   |
                jz @@RedrawOn                   ; >-----------------\
                                                ;                   |
                                                ;                   |
                call SaveScreenDiffs            ;                   |   < drawing ON, prev. was ON
                call DrawRegBox                 ;                   |
                mov si, offset buffer2          ;                   |
                call SaveScreen                 ;                   |
                                                ;                   |
                                                ;                   |
                jmp @@DoNotDrawEnd              ; >>========\\      |
            @@RedrawOn:                         ;           ||      |
                or byte ptr cs:[State], 10b     ;           ||      |
                                                ;           ||      |
                                                ;           ||      |
                mov si, offset buffer1          ;           ||      |   < drawing ON, prev. was OFF
                call SaveScreen                 ;           ||      |
                call DrawRegBox                 ;           ||      |
                mov si, offset buffer2          ;           ||      |
                call SaveScreen                 ;           ||      |
                                                ;           ||      |
                                                ;           ||      |
                jmp @@DoNotDrawEnd              ; >>========\\      |
        @@DoNotDraw:                            ; <---------++------/
                test byte ptr [State], 10b      ;           ||
                jz @@DoNotRedrawOff             ; >---------++------\
                and byte ptr cs:[State], not 10b;           ||      |
                                                ;           ||      |
                                                ;           ||      |
                call RestoreScreen              ;           ||      |   < drawing OFF, prev. was ON
                                                ;           ||      |
                                                ;           ||      |
                jmp @@DoNotDrawEnd              ; >>========\\      |
            @@DoNotRedrawOff:                   ; <---------++------/
                                                ;           ||
                                                ;           ||          < drawing OFF, prev. was OFF
                                                ;           ||
                                                ;           ||
        @@DoNotDrawEnd:                         ; <<========//

                mov al, 20h             ; Set interruptor free
                out 20h, al

                pop di si es ds dx cx bx ax     ; Stored regs


                pushf
                db 09Ah                 ; CALL FAR
Old08Ofs        dw 0                    ; call old 08 interruption
Old08Seg        dw 0

                iret
                endp

;------------------------------------------------
;------------------------------------------------

; .data
include ..\LianLib\Alphabet.asm
    ;   State variable:
    ; mask | meaning
    ; -----+---------
    ; 0001 | Box is on (1) / off (0)
    ; 0010 | Box was on (1) / off (0) last timer intr
State:          db 001h
Buffer1:        dw ((boxHeight + 2) * (boxWidth + 2)) DUP(?)    ; Info to restore (modified first screen)
Buffer2:        dw ((boxHeight + 2) * (boxWidth + 2)) DUP(?)    ; Info to compare (previous screen)
; .code

RegAX:      dw 0h
            db "rax"
RegBX:      dw 0h
            db "rbx"
RegCX:      dw 0h
            db "rcx"
RegDX:      dw 0h
            db "rdx"
RegSI:      dw 0h
            db " si"
RegDI:      dw 0h
            db " di"
RegBP:      dw 0h
            db " bp"
RegSP:      dw 0h
            db " sp"
RegDS:      dw 0h
            db " ds"
RegES:      dw 0h
            db " es"
RegSS:      dw 0h
            db " ss"
RegCS:      dw 0h
            db " cs"
RegIP:      dw 0h
            db " ip"
RegEnding:

include ..\LianLib\PrntNHex.asm
; include ..\LianLib\ProBox.asm
include ..\LianLib\DrawLine.asm


;------------------------------------------------
; Draws box for registers on the screen
;------------------------------------------------
; Entry:        ...
;
; Expects:      ES -> Video segment
;               DS -> Data segment
;
; Exit:         None
;
; Destroys:     AX BX CX DX DI
;               BX = start addr to draw
;               CH = height of box (without frame)
;               CL = width of box (without frame)
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     [bp + 2]
;               stored BP   [bp]
;               stored CX   [bp - 2]    // size
;               ...
;------------------------------------------------

DrawRegBox      proc
                push bp
                mov bp, sp                      ; Complete stack frame

                mov bx, 0d                      ; box position
                mov cl, boxWidth                ; box width
                mov ch, boxHeight               ; box height

                push cx

                mov ah, boxColor                ; box color

                                                ;-------------------------------------------
                                                ; Upper line
                mov di, bx
                mov cx, [bp - 2]
                mov ch, 0
                mov al, byte ptr [BoxAssetLU + boxTheme]
                push ax
                mov al, byte ptr [BoxAsset_U + boxTheme]
                push ax
                mov al, byte ptr [BoxAssetRU + boxTheme]
                push ax
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
                mov al, byte ptr [BoxAssetL_ + boxTheme];           |
                push ax                         ;                   |
                mov al, byte ptr [BoxAssetFI + boxTheme];           |
                push ax                         ;                   |
                mov al, byte ptr [BoxAssetR_ + boxTheme];           |
                push ax                         ;                   |
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
                mov al, byte ptr [BoxAssetLB + boxTheme]
                push ax
                mov al, byte ptr [BoxAsset_B + boxTheme]
                push ax
                mov al, byte ptr [BoxAssetRB + boxTheme]
                push ax
                call DrawLine
                add sp, 2*3d
                                                ;-------------------------------------------
                                                ;-------------------------------------------
                                                ; Printing regs

                mov bx, 10d                     ; start position
                mov dh, boxColor                ; color

                mov di, offset RegAX

        @@OneRegister:                          ; <-----------------\
                add bx, 160d                    ;                   |
                sub bx, 06d                     ;                   |
                                                ;                   |
                add di, 2d                      ;                   |
                                                ;                   |
                mov cx, 3d                      ;                   |
            @@OneChar:                          ; <-----\           |
                                                ;       |           |
                mov dl, cs:[di]                 ;       |           |
                mov es:[bx], dx                 ;       |           |
                                                ;       |           |
                inc di                          ;       |           |
                add bx, 2                       ;       |           |
                loop @@OneChar                  ; >-----/           |
                                                ;                   |
                mov dl, "="                     ;                   |
                mov es:[bx], dx                 ;                   |
                                                ;                   |
                sub di, 5d                      ;                   |
                                                ;                   |
                add bx, 08d                     ;                   |
                                                ;                   |
                mov ax, word ptr cs:[di]        ;                   |
                call PrintNHex                  ;                   |
                                                ;                   |
                sub di, offset RegAX            ;                   |
                add di, offset RegBX            ;                   |
                                                ;                   |
                cmp di, offset RegEnding        ;                   |
                jl @@OneRegister                ; >-----------------/


                pop cx
                pop bp                          ; Stack frame
                ret
DrawRegBox      endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Save screen into various buffer
;------------------------------------------------
; Entry:        SI = offset of the bufffer
;
; Expects:      ES -> Video segment
;
; Exit:         None
;
; Destroys:     AX BX CX DX DI SI
;               BX = start addr to draw
;               CH = height of box (with frame)
;               CL = width of box (with frame)
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     [bp + 2]
;               stored BP   [bp]
;               stored CX   [bp - 2]    // size
;               ...
;------------------------------------------------

SaveScreen      proc
                push bp
                mov bp, sp                      ; Complete stack frame

                mov bx, 0d                      ; box position
                mov cl, boxWidth                ; box area width
                add cl, 2d
                mov ch, boxHeight               ; box area height
                add ch, 2d

                push cx

                mov cx, [bp - 2]
                mov dh, 0
                mov dl, ch
@@OneLine:                                      ; <-----------------\
                                                ;                   |
                mov di, bx                      ;                   |
                mov cx, [bp - 2]                ;                   |
                mov ch, 0                       ;                   |
                                                ;                   |
            @@OneWord:                          ; <-----\           |
                                                ;       |           |
                mov ax, word ptr es:[di]        ;       |           |
                mov word ptr cs:[si], ax        ;       |           |
                add di, 2d                      ;       |           |
                add si, 2d                      ;       |           |
                                                ;       |           |
                loop @@OneWord                  ; >-----/           |
                                                ;                   |
                add bx, 160d                    ;                   |
                                                ;                   |
                dec dx                          ;                   |
                jnz @@OneLine                   ; >-----------------/

                pop cx
                pop bp                          ; Stack frame
                ret
SaveScreen      endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Restore screen from buffer1
;------------------------------------------------
; Entry:        ...
;
; Expects:      ES -> Video segment
;
; Exit:         None
;
; Destroys:     AX BX CX DX DI SI
;               BX = start addr to draw
;               CH = height of box (with frame)
;               CL = width of box (with frame)
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     [bp + 2]
;               stored BP   [bp]
;               stored CX   [bp - 2]    // size
;               ...
;------------------------------------------------

RestoreScreen   proc
                push bp
                mov bp, sp                      ; Complete stack frame

                mov bx, 0d                      ; box position
                mov cl, boxWidth                ; box area width
                add cl, 2d
                mov ch, boxHeight               ; box area height
                add ch, 2d

                push cx

                
                mov si, offset buffer1

                mov cx, [bp - 2]
                mov dh, 0
                mov dl, ch
@@OneLine:                                      ; <-----------------\
                                                ;                   |
                mov di, bx                      ;                   |
                mov cx, [bp - 2]                ;                   |
                mov ch, 0                       ;                   |
                                                ;                   |
            @@OneWord:                          ; <-----\           |
                                                ;       |           |
                mov ax, word ptr cs:[si]        ;       |           |
                mov word ptr es:[di], ax        ;       |           |
                add di, 2d                      ;       |           |
                add si, 2d                      ;       |           |
                                                ;       |           |
                loop @@OneWord                  ; >-----/           |
                                                ;                   |
                add bx, 160d                    ;                   |
                                                ;                   |
                dec dx                          ;                   |
                jnz @@OneLine                   ; >-----------------/

                pop cx
                pop bp                          ; Stack frame
                ret
RestoreScreen   endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Update saved screen in buffer1
;------------------------------------------------
; Entry:        SI = offset of the bufffer
;
; Expects:      ES -> Video segment
;
; Exit:         None
;
; Destroys:     AX BX CX DX DI SI
;               BX = start addr to draw
;               CH = height of box (with frame)
;               CL = width of box (with frame)
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     [bp + 2]
;               stored BP   [bp]
;               stored CX   [bp - 2]    // size
;               ...
;------------------------------------------------

SaveScreenDiffs proc
                push bp
                mov bp, sp                      ; Complete stack frame

                mov bx, 0d                      ; box position
                mov cl, boxWidth                ; box area width
                add cl, 2d
                mov ch, boxHeight               ; box area height
                add ch, 2d

                push cx

                mov si, offset buffer2

                mov cx, [bp - 2]
                mov dh, 0
                mov dl, ch
@@OneLine:                                      ; <-----------------\
                                                ;                   |
                mov di, bx                      ;                   |
                mov cx, [bp - 2]                ;                   |
                mov ch, 0                       ;                   |
                                                ;                   |
            @@OneWord:                          ; <-----\           |
                                                ;       |           |
                mov ax, word ptr es:[di]        ;       |           |
                cmp word ptr cs:[si], ax        ;       |           |
                je @@NoUpdate                   ; <<=\\ |           |
                                                ;    || |           |
                sub si, offset buffer2          ;    || |           |
                add si, offset buffer1          ;    || |           |
                mov word ptr cs:[si], ax        ;    || |           |
                sub si, offset buffer1          ;    || |           |
                add si, offset buffer2          ;    || |           |
                                                ;    || |           |
                @@NoUpdate:                     ; >>=// |           |
                add di, 2d                      ;       |           |
                add si, 2d                      ;       |           |
                                                ;       |           |
                loop @@OneWord                  ; >-----/           |
                                                ;                   |
                add bx, 160d                    ;                   |
                                                ;                   |
                dec dx                          ;                   |
                jnz @@OneLine                   ; >-----------------/

                pop cx
                pop bp                          ; Stack frame
                ret
SaveScreenDiffs endp

;------------------------------------------------
;------------------------------------------------


InterruptorMemEnd:

Main:
                cli
                mov bx, 0
                mov es, bx
                mov bx, 9*4                         ; DOS interruption address offset

                mov ax, es:[bx]                     ; Old interrupt-09 handler
                mov Old09Ofs, ax
                mov ax, es:[bx+2]
                mov Old09Seg, ax

                mov es:[bx], offset New09Int        ; Set my interrupt-09 handler
                mov ax, cs
                mov es:[bx+2], ax


                mov bx, 8*4                         ; DOS interruption address offset

                mov ax, es:[bx]                     ; Old interrupt-08 handler
                mov Old08Ofs, ax
                mov ax, es:[bx+2]
                mov Old08Seg, ax

                mov es:[bx], offset New08Int        ; Set my interrupt-08 handler
                mov ax, cs
                mov es:[bx+2], ax
                sti



                ; mov bx, 0b800h
                ; mov es, bx
                ; mov bx, 342d

                ; push ds ss cs

                ; mov dx, 00D00h
                ; pop ax
                ; call PrintNHex
                ; pop ax
                ; call PrintNHex
                ; pop ax
                ; call PrintNHex


                mov ax, 3100h
                mov dx, offset InterruptorMemEnd    ; Размер необходимой памяти
                shr dx, 4                           ; В параграфе 16 байт
                inc dx                              ; С округлением вверх

                int 21h

end             Start
