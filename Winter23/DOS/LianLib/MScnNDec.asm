;------------------------------------------------
; Scans number as decimal from string in memory
;------------------------------------------------
; Entry:        DS:SI = memory ptr
;
; Expects:      BX = 0
;               DL = terminator char 1
;               DH = terminator char 2
;               DF = 0 (CLD) [or backward]
;
; Exit:         BX = scanned number
;
; Destroys:     AX
;------------------------------------------------
;------------------------------------------------
MScnNDec        proc

@@ScanDigit:                                    ; <-------------------------\
                                                ;                           |
                ; mov ah, 01h                   ; getc -> al                |
                ; int 21h                       ; ^                         |
                lodsb                           ; char -> al                |
                                                ;                           |
                ; cmp al, 13d                   ; Stop scan if enter        |
                cmp al, dl                      ; Stop scan if terminator   |
                je @@EndScanDigit               ; >>========================|=======\\
                cmp al, dh                      ;                           |       ||
                je @@EndScanDigit               ; >>========================|=======\\
                                                ;                           |       ||
                ; mov cl, al                    ; Store al to cl            |       ||
                push ax                         ; Store ax                  |       ||
                push dx                         ; Store dx                  |       ||
                                                ;                           |       ||
                mov ax, bx                      ; bx *= 10                  |       ||
                mov dx, 10d                     ; ^                         |       ||
                mul dx                          ; ^                         |       ||
                mov bx, ax                      ; ^                         |       ||
                                                ;                           |       ||
                pop dx                          ; Retore dx                 |       ||
                pop ax                          ; Retore ax                 |       ||
                ; mov al, cl                    ; Retore al from cl         |       ||
                                                ;                           |       ||
                sub al, "0"                     ; ASCII "0" offset          |       ||
                                                ;                           |       ||
                mov ah, 0d                      ; bx += al                  |       ||
                add bx, ax                      ; ^                         |       ||
                                                ;                           |       ||
                jmp @@ScanDigit                 ; >-------------------------/       ||
                                                ;                                   ||
@@EndScanDigit:                                 ; <<================================//
                ret

MScnNDec        endp

;------------------------------------------------
;------------------------------------------------
