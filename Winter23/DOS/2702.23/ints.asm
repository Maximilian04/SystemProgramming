.model tiny
.code
org 100h

Start:          jmp Main



Main:           
                mov bx, 0b800h
                mov es, bx
                mov bx, 160d*5 + 80d

                mov ah, 4eh

Next:           in al, 60h
                mov bx, 160d*5 + 80d
                mov es:[bx], ax
                push ax
                add bx, 10
                call PrintNHex

                pop ax
                cmp al, 1
                jne Next

                mov ax, 4c00h
                int 21h


include ..\LianLib\PrntNHex.asm

.data
include ..\LianLib\Alphabet.asm

end             Start
