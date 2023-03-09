.model tiny
.code
.286
locals @@
org 100h

boxWidth  = 10d
boxHeight = 12d
boxTheme  = 2
boxColor  = 00Eh

Start:          jmp Main

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
                ; call SaveScreenDiffs            ;                   |   < drawing ON, prev. was ON
                call DrawRegBox                 ;                   |
                                                ;                   |
                                                ;                   |
                jmp @@DoNotDrawEnd              ; >>========\\      |
            @@RedrawOn:                         ;           ||      |
                or byte ptr cs:[State], 10b     ;           ||      |
                                                ;           ||      |
                                                ;           ||      |
                call SaveScreen                 ;           ||      |   < drawing ON, prev. was OFF
                call DrawRegBox                 ;                   |
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

                pop cx
                pop bp                          ; Stack frame
                ret
DrawRegBox      endp

;------------------------------------------------
;------------------------------------------------


;------------------------------------------------
; Save screen into buffer1
;------------------------------------------------
; Entry:        ...
;
; Expects:      ES -> Video segment
;               DS -> Data segment
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

                
                mov si, offset buffer1
                                                ; Upper line
                                                ; Middle line
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
                                                ; Bottom line

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
;               DS -> Data segment
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
                                                ; Upper line
                                                ; Middle line
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
                                                ; Bottom line

                pop cx
                pop bp                          ; Stack frame
                ret
RestoreScreen   endp

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
