;------------------------------------------------
; Scans number as hexagen from string in memory
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
MScnNHex        proc

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
                                                ;                           |       ||  ||
                shl bx, 4d                      ; bx *= 16                  |       ||  ||
                                                ;                           |       ||  ||
                                                ;                           |       ||  ||
                push bx                         ; Store bx                  |       ||  ||
                                                ;                           |       ||  ||
                mov bx, "a"                     ;                           |       ||  ||
                cmp al, bl                      ;                           |       ||  ||
                jl @@Nextaf                     ;                           |       ||  ||
                mov bx, "f"                     ;                           |       ||  ||
                cmp al, bl                      ;                           |       ||  ||
                jg @@Nextaf                     ;                           |       ||  ||
                sub al, "a"                     ; ASCII "0" offset          |       ||  ||
                add al, 0ah                     ; ^                         |       ||  ||
@@Nextaf:                                       ;                           |       ||  ||
                mov bx, "A"                     ;                           |       ||  ||
                cmp al, bl                      ;                           |       ||  ||
                jl @@NextAFCAPS                 ;                           |       ||  ||
                mov bx, "F"                     ;                           |       ||  ||
                cmp al, bl                      ;                           |       ||  ||
                jg @@NextAFCAPS                 ;                           |       ||  ||
                sub al, "A"                     ; ASCII "0" offset          |       ||  ||
                add al, 0Ah                     ; ^                         |       ||  ||
@@NextAFCAPS:                                   ;                           |       ||  ||
                mov bx, "0"                     ;                           |       ||  ||
                cmp al, bl                      ;                           |       ||  ||
                jl @@Next09                     ;                           |       ||  ||
                mov bx, "9"                     ;                           |       ||  ||
                cmp al, bl                      ;                           |       ||  ||
                jg @@Next09                     ;                           |       ||  ||
                sub al, "0"                     ; ASCII "0" offset          |       ||  ||
                ; add al, 0                     ; ^                         |       ||  ||
@@Next09:                                       ;                           |       ||  ||
                                                ;                           |       ||  ||
                pop bx                          ; Restore bx                |       ||  ||
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

MScnNHex        endp

;------------------------------------------------
;------------------------------------------------
