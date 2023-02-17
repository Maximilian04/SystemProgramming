;------------------------------------------------
; Prints number as hexagen to vidmem
;------------------------------------------------
; Entry:        AX = number to print
;               BX = start addr to print
;
; Expects:      ES -> Video segment
;               DH = color code
;
; Exit:         None
;
; Destroys:     AX BX CX DL Si
;------------------------------------------------
;------------------------------------------------
PrintNHex       proc

                mov cx, 4d                      ; 4 digits in 2 byte in ax

@@PrintDigit:                                   ; <-------------------------\
                                                ;                           |
                mov dl, 00001111b               ; Mask                      |
                and dl, al                      ;                           |
                                                ;                           |
                mov si, dx                      ; dl -> si                  |
                and si, 0Fh                     ;                           |
                                                ;                           |
                mov dl, byte ptr [Alphabet]+si  ; ASCII "0" offset          |
                                                ;                           |
                mov word ptr es:[bx], dx        ; Print dl on position bx   |
                                                ;                           |
                dec bx                          ; Next digit                |
                dec bx                          ; ^                         |
                                                ;                           |
                shr ax, 4d                      ; ax >> 4                   |
                                                ;                           |
                loop @@PrintDigit               ; >-------------------------/

                ret

PrintNHex       endp

;------------------------------------------------
;------------------------------------------------
