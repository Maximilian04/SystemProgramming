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
                pusha                   ; Stored regs
                ; mov ax, cs
                ; mov ds, ax

                in al, 60h              ; Catch key code

                cmp al, 01Dh            ; ctrl is pressed
                je @@ControlKey1
                cmp al, 02Ah            ; shift is pressed
                je @@ControlKey2

                jmp @@NotControlKey
            @@ControlKey1:
                                                ; CTRL is pressed


                mov di, word ptr cs:[CurPos]
                mov bx, 0Eh

@@CycleChar:                                    ; <-------------------------\
                cmp di, offset StrEnd           ;                           |
                jge @@CycleEnd                  ; >-----\                   |
                                                ;       |                   |
                mov ch, 0                       ;       |                   |
                mov cl, cs:[di]                 ;       |                   |
                inc di                          ;       |                   |
                                                ;       |                   |
                mov ah, 5h                      ; put cx to keyboard        |
                int 16h                         ;       |                   |
                                                ;       |                   |
                dec bx                          ;       |                   |
                jnz @@CycleChar                 ; >-----+-------------------/
                                                ;       |
            @@CycleEnd:                         ; <-----/
                mov word ptr cs:[CurPos], di


                jmp @@NotControlKey
            @@ControlKey2:
                                                ; SHIFT is pressed


                mov di, word ptr cs:[PswPos]
                mov bx, 0Eh

@@CycleChar2:                                   ; <-------------------------\
                cmp di, offset PswEnd           ;                           |
                jge @@CycleEnd2                 ; >-----\                   |
                                                ;       |                   |
                mov ch, 0                       ;       |                   |
                mov cl, cs:[di]                 ;       |                   |
                inc di                          ;       |                   |
                                                ;       |                   |
                mov ah, 5h                      ; put cx to keyboard        |
                int 16h                         ;       |                   |
                                                ;       |                   |
                dec bx                          ;       |                   |
                jnz @@CycleChar2                ; >-----+-------------------/
                                                ;       |
            @@CycleEnd2:                        ; <-----/
                mov word ptr cs:[PswPos], di



            @@NotControlKey:


                popa                    ; Stored regs
                pushf
                db 09Ah                 ; CALL FAR
Old09Ofs        dw 0                    ; call old 09 interruption
Old09Seg        dw 0

                iret
                endp

;------------------------------------------------
;------------------------------------------------

CurPos:         dw offset String
String:
                db (50h - 2h) DUP(167d)
                db 0Ah DUP(2d)
                ; db 1F8h DUP("a")
                ; db "You are great!"
StrEnd:

PswPos:         dw offset Psw
Psw:
                db "Old"
                ; db 040h 
                ; db 03Ah 
                ; db 0D2h 
                ; db 071h 
                ; db 0CEh 
                ; db 049h 
                ; db 08Eh 
                ; db 073h 
                ; db 05Ch 
                ; db 002h
PswEnd:

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
                sti

                
                mov ax, 3100h
                mov dx, offset InterruptorMemEnd    ; Размер необходимой памяти
                shr dx, 4                           ; В параграфе 16 байт
                inc dx                              ; С округлением вверх

                int 21h

                ; mov ax, 4c00h                   ; exit(0)
                ; int 21h

end             Start
