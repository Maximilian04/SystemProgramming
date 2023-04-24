.model tiny
.code
locals @@

org 80h
ArgCount:       db ?
Args:           db ?

org 100h

Start:
                mov di, offset String
                call StrLen
                mov dx, cx
                test dx, dx

                mov ax, 0b800h                  ; адрес сегмента с видеопамятью -> es
                mov es, ax                      ;

                ; mov ax, ss                      ; Segment with stack, code, etc.
                ; mov ds, ax                      ;

                ; mov ah, 00001010b               ; Light green on black
                ; mov bx, 160d*18 + 160d/2 - 18d*2 + 4d; Середина строчки
                ; mov ch, 5                       ; Height
                ; mov cl, 18                      ; Width
                ; call DrawBox
                mov di, 160d*18 + 160d/2 - 18d*2 + 4d; Середина строчки
                mov cx, 32                       ; Width
                mov al, 0DAh
                call MemSet

                mov ax, ds
                mov es, ax
                mov ax, offset String1
                mov si, ax
                mov ax, offset String2
                mov di, ax
                call StrCmp
                jnl heh

                mov ax, 0b800h                  ; адрес сегмента с видеопамятью -> es
                mov es, ax                      ;

                mov ax, dx
                mov dh, 02h
                mov bx, di
                call PrintNDec
heh:

                ; mov dh, 00000010b               ; Dark green on black
                ; pop ax                          ; Scanned number
                ; push ax                         ;

                ; call PrintNBin

                mov ax, 4c00h                   ; exit(0)
                int 21h

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
                scasb                           ;                           |
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

include ..\LianLib\ScanNDec.asm
include ..\LianLib\PrntNBin.asm
include ..\LianLib\PrntNHex.asm
include ..\LianLib\PrntNDec.asm

include ..\LianLib\DrawLine.asm

.data
include ..\LianLib\Alphabet.asm
String:     db "12345678910", 0h
String1:     db "aa", 0h
String2:     db "aab", 0h

end             Start
