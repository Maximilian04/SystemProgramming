;===========================================
;   printf.asm
;   NASM printf implication
;===========================================

;-------------------------------------------
; External stuff
;-------------------------------------------

extern GetStdHandle                     ; kernel32.dll
extern WriteConsoleA                    ; kernel32.dll


;-------------------------------------------
; printfm - My printf implementation
;-------------------------------------------
; Entry:        (All on stack):
;               [1st] format string pointer
;               [2nd] 1st printf arg
;               [3rd] 2nd printf arg
;               [...] ...
;
; Expects:      
;
; Exit:         None
;
; Destroys:     
;-------------------------------------------
; Stack frame:
;               ...
;               2st         [rbp + 24] // printf arg
;               1st         [rbp + 16] // format string ptr
;               retAddr     [rbp + 8]
;               stored BP   [rbp]
;               stored rbx  [rbp - 8]
;               stored r12  [rbp - 16]
;               stored r13  [rbp - 24]
;               stored rsi  [rbp - 32]
;               stored rdi  [rbp - 40]
;            hConsoleOutput [rbp - 48]
;               ...
formatStrOffset               equ +16
hConsoleOutputOffset          equ -48
;-------------------------------------------
section .text
global printfm
printfm:
        push rbp
        mov rbp, rsp                    ; Stack frame
        push rbx                        ; store external rbx to stack
        push r12                        ; store external r12 to stack
        push r13                        ; store external r13 to stack
        push rsi                        ; store external rsi to stack
        push rdi                        ; store external rdi to stack


        mov rcx, STD_OUTPUT_HANDLE      ; STD_OUTPUT_HANDLE = -11
        call GetStdHandle               ; rax = hConsoleOutput = GetStdHandle(-11)

        push rax                        ; hConsoleOutput -> stack


        mov rbx, 0
        mov r12, [rbp + formatStrOffset]; r12 = format string ptr
        mov r13, ModeNormal             ; r13 = mode ( = 0)


        jmp .ScanBeginning              ;               >>>>>>>>>>>>>>>>
                                        ; <---------------------\
                                        ;!!!!!!                 |
            ..@ModeProcent:             ;                       |
                mov r13, ModeNormal     ;                       |
                                        ;                       |
                mov al, "%"             ;                       |
                cmp bl, al              ;                       |
                jne .NotProcentSymb     ; >>====\\              |
                call printChar          ;       ||              |
                jmp .ScanNext           ;       ||      >>>>>>>>>>>>>>>>
                                        ;       ||              |
                .NotProcentSymb:        ; <<====//              |
                mov al, "b"             ;                       |
                cmp bl, al              ;                       |
                jl .OutOfTable          ; >>====\\              |
                mov al, "x"             ;       ||              |
                cmp bl, al              ;       ||              |
                jg .OutOfTable          ; >>====\\              |
                                        ;       ||              |
                call [ProcentCallTable + 8 * (rbx - "b")];      |
                jmp .ScanNext           ;       ||      >>>>>>>>>>>>>>>>
                                        ;       ||              |
            .OutOfTable:                ; <<====//              |
                call printChar          ;                       |
                jmp .ScanNext           ;               >>>>>>>>>>>>>>>>
                                        ;                       |
                                        ;!!!!!!                 |
            ..@ModeNormal:              ;                       |
                mov al, "%"             ;                       |
                cmp al, bl              ;                       |
                jne .NotProcent         ; >>====\\              |
                mov r13, ModeProcent    ;       ||              |
                jmp .ScanNext           ;       ||      >>>>>>>>>>>>>>>>
                                        ;       ||              |
                .NotProcent:            ; <<====//              |
                                        ;                       |
                call printChar          ;                       |
                jmp .ScanNext           ;               >>>>>>>>>>>>>>>>
                                        ;!!!!!!                 |
                                        ;                       |
                                        ;                       |
            .ScanNext:                  ;               <<<<<<<<<<<<<<<<
                inc r12                 ;                       |
            .ScanBeginning:             ;               <<<<<<<<<<<<<<<<
                mov bl, [r12]           ; bl = next character   |
                test bl, bl             ;                       |
                jz .Finish              ; >>====\\              |
                jmp [ModeCallTable + 8 * r13]; >||--------------/
        .Finish:                        ; <<====//


        pop rax                         ; remove hConsoleOutput

        pop rdi                         ; restore external rdi
        pop rsi                         ; restore external rsi
        pop r13                         ; restore external r13
        pop r12                         ; restore external r12
        pop rbx                         ; restore external rbx
        pop rbp
        ret
;-------------------------------------------
;-------------------------------------------


;-------------------------------------------
; printChar - Print one character (no rbp func)
;-------------------------------------------
; Entry:        r12  - ptr to char
;
; Expects:      [rbp + hConsoleOutputOffset] = hConsoleOutput
;
; Exit:         None
;
; Destroys:     
;-------------------------------------------
; Stack frame:
;               ...
;               retAddr     [...]
;               ...
;-------------------------------------------
section .text
printChar:
        mov rcx, [rbp + hConsoleOutputOffset]
        mov rdx, r12                    ; string ptr
        mov r8, 1                       ; one character
        mov r9, 0
        sub rsp, (8*4)
        push qword 0
        call WriteConsoleA              ; WriteConsole  (hConsoleOutput, ptr, 1, 0, 0)
        add rsp, (8*5)

        ret
;-------------------------------------------
;-------------------------------------------


;-------------------------------------------
; x64 c calling convention
;
;       1st     RCX
;       2nd     RDX	
;	3rd     R8	
;	4th     R9
;       5th+    to stack
;-------------------------------------------


;-------------------------------------------
; Constants
;-------------------------------------------
section .data

STD_OUTPUT_HANDLE equ (-11)


        ; Mode table:
        ;        value  | mode
        ;       --------+---------------
        ;          0    | normal
        ;          1    | character after %

ModeNormal      equ 0
ModeProcent     equ 1

ModeCallTable   dq ..@ModeNormal
                dq ..@ModeProcent

ProcentCallTable dq printChar   ; b
                dq printChar    ; c
                dq printChar    ; d
                dq 10 dup(printChar)
                dq printChar    ; o
                dq 3 dup(printChar)
                dq printChar    ; s
                dq 4 dup(printChar)
                dq printChar    ; x

; OUTDATED:     ----------------------------
;         ;          1    | special symbol after \ (\n, \t)
; ModeBackslash   equ 1
;                 dq ..@ModeBackslash
;-------------------------------------------
;-------------------------------------------
; ld hello.obj "C:\Windows\System32\kernel32.dll" "C:\Windows\System32\user32.dll" -e __start
;       or
; nasm printfm.asm -f win64
;-------------------------------------------
;-------------------------------------------
