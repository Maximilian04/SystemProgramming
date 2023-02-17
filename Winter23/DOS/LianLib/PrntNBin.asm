;------------------------------------------------
; Prints number as binary to vidmem
;------------------------------------------------
; Entry:        AX = number to print
;               BX = start addr to print
;
; Expects:      ES -> Video segment
;               DH = color code
;
; Exit:         None
;
; Destroys:     AX BX CX DL
;------------------------------------------------
;------------------------------------------------
PrintNBin       proc

                mov cx, 16d                     ; 16 bit in 2 byte in ax

@@PrintDigit:                                   ; <-------------------------\
                                                ;                           |
                mov dl, 00000001b               ; Mask                      |
                and dl, al                      ;                           |
                add dl, 30h                     ; ASCII "0" offset          |
                                                ;                           |
                mov word ptr es:[bx], dx        ; Print dl on position bx   |
                                                ;                           |
                dec bx                          ; Next digit                |
                dec bx                          ; ^                         |
                                                ;                           |
                shr ax, 1d                      ; ax >> 1                   |
                                                ;                           |
                loop @@PrintDigit               ; >-------------------------/

                ret

PrintNBin       endp

;------------------------------------------------
;------------------------------------------------
