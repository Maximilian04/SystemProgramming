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
                mov es:[bx], ax

                cmp al, 1
                jne Next

                mov ax, 4c00h
                int 21h

end             Start
