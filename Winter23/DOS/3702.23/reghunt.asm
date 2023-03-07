.model tiny
.code
.286
locals @@
org 100h

Start:          jmp Main


State:          db 0DDh


;------------------------------------------------
; Keyboard intterupt handler
;------------------------------------------------
;
;   Catches control keys & sets (State) variable
;
;------------------------------------------------

New09Int        proc
                push ax bx es           ; Stored regs

                in al, 60h              ; Catch key code

                cmp al, 01Dh
                je @@ControlKey1
                cmp al, 09Dh
                je @@ControlKey2

                jmp @@NotControlKey
            @@ControlKey1:
                                        ; Invert State variable
                ; inc byte ptr [State]
                xor byte ptr [State], 01b

                jmp @@NotControlKey
            @@ControlKey2:
                                        ; Invert State variable
                ; mov byte ptr [State], 00b

                jmp @@NotControlKey
            @@NotControlKey:

                in al, 61h              ; Set interruptor free
                or al, 80h
                out 61h, al
                and al, not 80h
                out 61h, al

                mov al, 20h             ; Set interruptor free
                out 20h, al


                pop es bx ax            ; Stored regs
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
                push ax bx cx dx ds es si  ; Stored regs


                mov bx, 0b800h
                mov es, bx
                mov bx, 200d

                mov al, byte ptr [State]
                mov byte ptr es:[bx], al

                mov dx, cs
                mov ds, dx
                mov dx, 00A00h
                sub bx, 2d
                mov ah, 0d
                call PrintNHex

                cmp byte ptr [State], 01b
                jne @@DoNotDraw

                ; mov byte ptr es:[bx], 61d

                jmp @@DoNotDrawEnd
            @@DoNotDraw:

                ; mov byte ptr es:[bx], 62d

            @@DoNotDrawEnd:
                ; in al, 61h              ; Set interruptor free
                ; or al, 80h
                ; out 61h, al
                ; and al, not 80h
                ; out 61h, al

                mov al, 20h             ; Set interruptor free
                out 20h, al

                pop si es ds dx cx bx ax   ; Stored regs


                pushf
                db 09Ah                 ; CALL FAR
Old08Ofs        dw 0                    ; call old 08 interruption
Old08Seg        dw 0

                iret
                endp

;------------------------------------------------
;------------------------------------------------


include ..\LianLib\Alphabet.asm
include ..\LianLib\PrntNHex.asm
include ..\LianLib\ProBox.asm
include ..\LianLib\DrawLine.asm


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

                mov ax, 3100h
                mov dx, offset InterruptorMemEnd    ; Размер необходимой памяти
                shr dx, 4                           ; В параграфе 16 байт
                inc dx                              ; С округлением вверх

                int 21h

end             Start
