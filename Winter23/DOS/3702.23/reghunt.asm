.model tiny
.code
.286
locals @@
org 100h

Start:          jmp Main


New09Int        proc                    ; Keyboard interruption
                                        ; Must catch control keys
                push ax bx es           

                in al, 60h              ; Catch key code

                in al, 61h              ; Set interruptor free
                or al, 80h
                out 61h, al
                and al, not 80h
                out 61h, al

                mov al, 20h             ; Set interruptor free
                out 20h, al

                pop es bx ax


                pushf
                db 09Ah                     ; CALL FAR
Old09Ofs        dw 0                        ; call old 09 interruption
Old09Seg        dw 0

                push ax bx es

                pop es bx ax

                iret
                endp

ProgramEnd:


Main:
                cli
                mov bx, 0
                mov es, bx
                mov bx, 9*4                 ; DOS interruption address offset

                mov ax, es:[bx]             ; Old interrupt-09 handler
                mov Old09Ofs, ax
                mov ax, es:[bx+2]
                mov Old09Seg, ax

                mov es:[bx], offset New09Int; Set my interrupt-09 handler
                mov ax, cs
                mov es:[bx+2], ax
                sti

                mov ax, 3100h
                mov dx, offset ProgramEnd   ; Размер необходимой памяти
                shr dx, 4                   ; В параграфе 16 байт
                inc dx                      ; С округлением вверх

                int 21h

end             Start
