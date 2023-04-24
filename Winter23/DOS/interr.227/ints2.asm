.model tiny
.code
org 100h

Start:          jmp Main



Main:           
                cli
                xor bx, bx
                mov es, bx
                mov bx, 9*4

                mov ax, es:[bx]
                mov Old09Ofs, ax
                mov ax, es:[bx+2]
                mov Old09Seg, ax

                mov es:[bx], offset New09
                mov ax, cs
                mov es:[bx+2], ax
                sti

                mov ax, 3100h
                mov dx, offset ProgramEnd   ; Размер необходимой памяти
                shr dx, 4                   ; В параграфе 16 байт
                inc dx                      ; С округлением вверх

                int 21h

New09           proc
                push ax bx es

                mov bx, 0b800h
                mov es, bx
                mov bx, 160d*5 + 80d

                mov ah, 4eh
                in al, 60h
                mov es:[bx], ax

                in al, 61h
                or al, 80h
                out 61h, al
                and al, not 80h
                out 61h, al

                mov al, 20h
                out 20h, al

                pop es bx ax
                
                
                ;iret
                
                ;db 0eah                     ; JMP FAR

                pushf
                db 09Ah                     ; CALL FAR
Old09Ofs        dw 0
Old09Seg        dw 0

                push ax bx es
                mov bx, 0b800h
                mov es, bx
                mov bx, 160d*5 + 80d - 2
                mov ah, 2fh
                
                in al, 60h
                mov al, "Q"

                mov es:[bx], ax
                pop es bx ax
                
                iret
                
                endp

ProgramEnd:
end             Start
