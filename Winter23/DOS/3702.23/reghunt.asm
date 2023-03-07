.model tiny
.code
.286
locals @@
org 100h

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

                ; cmp byte ptr [State], 011b
                test byte ptr [State], 01b
                jz @@DoNotDraw

                ; xor byte ptr [State], 01b
                
                call DrawRegBox

                jmp @@DoNotDrawEnd
            @@DoNotDraw:

                ; mov byte ptr es:[bx], 62d

            @@DoNotDrawEnd:

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
State:          db 001h
include ..\LianLib\Alphabet.asm
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
                mov cl, 10d                     ; box width
                mov ch, 12d                     ; box height

                push cx

                mov ah, 00Eh                    ; box color

                                                ;-------------------------------------------
                                                ; Upper line
                mov di, bx
                mov cx, [bp - 2]
                mov ch, 0
                mov al, byte ptr [BoxAssetLU + 2]
                push ax
                mov al, byte ptr [BoxAsset_U + 2]
                push ax
                mov al, byte ptr [BoxAssetRU + 2]
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
                mov al, byte ptr [BoxAssetL_ + 2];                  |
                push ax                         ;                   |
                mov al, byte ptr [BoxAssetFI + 2];                  |
                push ax                         ;                   |
                mov al, byte ptr [BoxAssetR_ + 2];                  |
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
                mov al, byte ptr [BoxAssetLB + 2]
                push ax
                mov al, byte ptr [BoxAsset_B + 2]
                push ax
                mov al, byte ptr [BoxAssetRB + 2]
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
