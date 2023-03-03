;------------------------------------------------
; Scans number as decimal from string in memory
;------------------------------------------------
; Entry:        DS:SI = memory ptr
;
; Expects:      BX = 0
;               DL = terminator char 1
;               DH = terminator char 2 (TerminatorEnd)
;               DF = 0 (CLD) [or backward]
;
; Exit:         BX = scanned number
;               SI to next word
;               AX = 0 if terminator, 1 if TerminatorEnd
;
; Destroys:     None
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
                je @@TermScanDigit              ; >>========================|=======\\
                cmp al, dh                      ;                           |       ||
                je @@TerminatorEndScanDigit     ; >>========================|===========\\
                                                ;                           |       ||  ||
                ; mov cl, al                    ; Store al to cl            |       ||  ||
                push ax                         ; Store ax                  |       ||  ||
                push dx                         ; Store dx                  |       ||  ||
                                                ;                           |       ||  ||
                mov ax, bx                      ; bx *= 10                  |       ||  ||
                mov dx, 10d                     ; ^                         |       ||  ||
                mul dx                          ; ^                         |       ||  ||
                mov bx, ax                      ; ^                         |       ||  ||
                                                ;                           |       ||  ||
                pop dx                          ; Restore dx                |       ||  ||
                pop ax                          ; Restore ax                |       ||  ||
                ; mov al, cl                    ; Restore al from cl        |       ||  ||
                                                ;                           |       ||  ||
                sub al, "0"                     ; ASCII "0" offset          |       ||  ||
                                                ;                           |       ||  ||
                mov ah, 0d                      ; bx += al                  |       ||  ||
                add bx, ax                      ; ^                         |       ||  ||
                                                ;                           |       ||  ||
                jmp @@ScanDigit                 ; >-------------------------/       ||  ||
                                                ;                                   ||  ||
@@TermScanDigit:                                ; <<================================//  ||
                mov ax, 0                       ;                                       ||
                jmp @@EndProc                   ; >-----\                               ||
@@TerminatorEndScanDigit:                       ; <<====|===============================//
                mov ax, 1                       ;       |
@@EndProc:                                      ; <-----/
                ret

MScnNDec        endp

;------------------------------------------------
;------------------------------------------------
