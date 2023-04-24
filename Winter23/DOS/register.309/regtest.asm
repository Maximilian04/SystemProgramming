.model tiny
.code
.286
locals @@
org 100h

Start:

                mov bx, 0736h
                mov ds, bx
                mov bx, 0737h
                mov es, bx

                mov ax, 0739h
                mov bx, 0740h
                mov cx, 0731h
                mov dx, 0732h
                mov si, 0733h
                mov di, 0734h
                mov bp, 0735h

                mov ah, 01h                     ; getc -> al
                int 21h                         ; ^
                push ax
                push ax
                mov ah, 01h                     ; getc -> al
                int 21h                         ; ^
                push ax
                mov ah, 01h                     ; getc -> al
                int 21h                         ; ^


                mov ax, 4c00h                   ; exit(0)
                int 21h

include ..\LianLib\ScanNDec.asm

.data
include ..\LianLib\Alphabet.asm

end             Start
