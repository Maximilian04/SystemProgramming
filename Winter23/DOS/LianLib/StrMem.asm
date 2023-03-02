;------------------------------------------------
; Compare (num) bytes from (src) and (dst)
;------------------------------------------------
; Entry:        CX = num
;               DS:SI = src
;               ES:DI = dst
;
; Expects:      DF = 0 (CLD)
;
; Exit:         Compare flags
;
; Destroys:     AX CX SI DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).

MemCmp          proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame

                xor ax, ax                      ; AL = 0

@@CountStep:                                    ; <-------------------------\
                                                ;                           |
                cmpsb                           ;                           |
                jne @@CountEnd                  ; >>===\\                   |
                dec cx                          ;      ||                   |
                cmp ax, cx                      ;      ||                   |
                jne @@CountStep                 ; >----++-------------------/
@@CountEnd:                                     ; <<===//

                ; pop bp                          ; Stack frame
                ret
MemCmp          endp

;------------------------------------------------
;------------------------------------------------

;------------------------------------------------
; Compare null-terminated strings (src) and (dst)
;------------------------------------------------
; Entry:        DS:SI = src
;               ES:DI = dst
;
; Expects:      DF = 0 (CLD)
;
; Exit:         Compare flags
;
; Destroys:     AL SI DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).

StrCmp          proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame

                xor al, al                      ; AL = 0

@@CountStep:                                    ; <-------------------------\
                                                ;                           |
                cmpsb                           ;                           |
                jne @@CountEnd                  ; >>===\\                   |
                cmp al, es:[di]                 ;      ||                   |
                jne @@CountStep                 ; >----++-------------------/
@@CountEnd:                                     ; <<===//

                ; pop bp                          ; Stack frame
                ret
StrCmp          endp

;------------------------------------------------
;------------------------------------------------

;------------------------------------------------
; Copies the null-terminated string (src) into the (dst)
;------------------------------------------------
; Entry:        DS:SI = src
;               ES:DI = dst
;
; Expects:      DF = 0 (CLD)
;
; Exit:         None
;
; Destroys:     AL SI DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).

StrCpy          proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame

                xor al, al                      ; AL = 0

@@CountStep:                                    ; <-------------------------\
                movsb                           ;                           |
                cmp al, es:[di]                 ;                           |
                jne @@CountStep                 ; >-------------------------/

                ; pop bp                          ; Stack frame
                ret
StrCpy          endp

;------------------------------------------------
;------------------------------------------------

;------------------------------------------------
; Count the length of the null-terminated string (str)
;------------------------------------------------
; Entry:        ES:DI = str
;
; Expects:      DF = 0 (CLD)
;
; Exit:         CX = length
;
; Destroys:     AL DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).

StrLen          proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame

                xor al, al                      ; AL = 0
                xor cx, cx                      ; CX = 0

@@CountStep:                                    ; <-------------------------\
                inc cx                          ;                           |
                scasb                           ;                           |
                jne @@CountStep                 ; >-------------------------/

                dec cx

                ; pop bp                          ; Stack frame
                ret
StrLen          endp

;------------------------------------------------
;------------------------------------------------

;------------------------------------------------
; Copies the (num) bytes from (src) to (dst)
;------------------------------------------------
; Entry:        CX = num
;               DS:SI = src
;               ES:DI = dst
;
; Expects:      DF = 0 (CLD)
;
; Exit:         None
;
; Destroys:     CX SI DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).

MemCpy          proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame

                rep movsb

                ; pop bp                          ; Stack frame
                ret
MemCpy          endp

;------------------------------------------------
;------------------------------------------------

;------------------------------------------------
; Sets (num) bytes of the memory pointed by (ptr) to the specified (value)
;------------------------------------------------
; Entry:        CX = num
;               AL = value
;               ES:DI = ptr
;
; Expects:      DF = 0 (CLD)
;
; Exit:         None
;
; Destroys:     CX DI
;------------------------------------------------
; Stack frame:
;               ...
;               retAddr     []
;               ...
;------------------------------------------------
;Направление просмотра  зависит  от флага направления DF, значение  которого  можно  менять  с  помощью команд CLD (DF:=0) и STD (DF:=1).

MemSet          proc
                ; push bp
                ; mov bp, sp                      ; Complete stack frame

                rep stosb

                ; pop bp                          ; Stack frame
                ret
MemSet          endp

;------------------------------------------------
;------------------------------------------------
