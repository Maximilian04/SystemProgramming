;------------------------------------------------
; Scans number as decimal
;------------------------------------------------
; Entry:        none
;
; Expects:      BX = 0
;
; Exit:         BX = number to print
;
; Destroys:     AX CL Si
;------------------------------------------------
;------------------------------------------------
ScanNDec        proc

@@ScanDigit:                                    ; <??????????????????????????
                                                ;                           ?
                mov ah, 01h                     ; getc -> al                ?
                int 21h                         ; ^                         ?
                                                ;                           ?
                cmp al, 13d                     ; Stop scan if enter        ?
                je @@EndScanDigit               ; >>?????????????????????????????????
                                                ;                           ?       ?
                mov cl, al                      ; Store al to cl            ?       ?
                                                ;                           ?       ?
                mov ax, bx                      ; bx *= 10                  ?       ?
                mov si, 10d                     ; ^                         ?       ?
                mul si                          ; ^                         ?       ?
                mov bx, ax                      ; ^                         ?       ?
                                                ;                           ?       ?
                mov al, cl                      ; Retore al from cl         ?       ?
                                                ;                           ?       ?
                sub al, "0"                     ; ASCII "0" offset          ?       ?
                                                ;                           ?       ?
                mov ah, 0d                      ; bx += al                  ?       ?
                add bx, ax                      ; ^                         ?       ?
                                                ;                           ?       ?
                jmp @@ScanDigit                 ; >??????????????????????????       ?
                                                ;                                   ?
@@EndScanDigit:                                 ; <<?????????????????????????????????
                ret

ScanNDec        endp

;------------------------------------------------
;------------------------------------------------
