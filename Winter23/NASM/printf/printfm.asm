;===========================================
;   printfm.asm
;   NASM printf implementation
;===========================================

;-------------------------------------------
; External stuff
;-------------------------------------------

extern GetStdHandle                     ; kernel32.dll
extern WriteConsoleA                    ; kernel32.dll

%include "printBOXD.asm"


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
; Destroys:     rax rcx rdx r8 r9
;-------------------------------------------
; Stack frame:
;               ...
;               2st         [rbp + 24] // printf arg
;               1st         [rbp + 16] // format string ptr
;               retAddr     [rbp + 8]
;               stored BP   [rbp]
;            hConsoleOutput [rbp - 8]
;               stored rbx  [rbp - 16]
;               stored r12  [rbp - 24]
;               stored r13  [rbp - 32]
;               stored r14  [rbp - 40]
;               stored rsi  [rbp - 48]
;               stored rdi  [rbp - 56]
;               ...
formatStrOffset               equ +16
formatArgOffset               equ +24
hConsoleOutputOffset          equ -8
;-------------------------------------------
section .text
global printfm
printfm:
        push rbp
        mov rbp, rsp                    ; Stack frame
        push 0                          ; space for hConsoleOutput
        push rbx                        ; store external rbx to stack
        push r12                        ; store external r12 to stack
        push r13                        ; store external r13 to stack
        push r14                        ; store external r13 to stack
        push rsi                        ; store external rsi to stack
        push rdi                        ; store external rdi to stack


        mov rcx, STD_OUTPUT_HANDLE      ; STD_OUTPUT_HANDLE = -11
        call GetStdHandle               ; rax = hConsoleOutput = GetStdHandle(-11)

        mov [rbp + hConsoleOutputOffset], rax; hConsoleOutput -> stack


        mov rbx, 0
        mov r12, [rbp + formatStrOffset]; r12 = format string ptr
        mov r13, ModeNormal             ; r13 = mode ( = 0)
        mov r14, rbp
        add r14, formatArgOffset        ; r14 = ptr to varargs


        jmp .ScanBeginning              ;               >>>>>>>>>>>>>>>>
                                        ; <---------------------\
                                        ;!!!!!!                 |
            ..@ModeProcent:             ;                       |
                mov r13, ModeNormal     ;                       |
                                        ;                       |
                cmp bl, "%"             ;                       |
                jne .NotProcentSymb     ; >>====\\              |
                call printChar          ;       ||              |
                jmp .ScanNext           ;       ||      >>>>>>>>>>>>>>>>
                                        ;       ||              |
                .NotProcentSymb:        ; <<====//              |
                cmp bl, "b"             ;                       |
                jl .OutOfTable          ; >>====\\              |
                cmp bl, "x"             ;       ||              |
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
                cmp bl, "%"             ;                       |
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


        pop rdi                         ; restore external rdi
        pop rsi                         ; restore external rsi
        pop r14                         ; restore external r14
        pop r13                         ; restore external r13
        pop r12                         ; restore external r12
        pop rbx                         ; restore external rbx
        add rsp, 8                      ; remove hConsoleOutput
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
; Destroys:     rax rcx, rdx, r8, r9
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
; printS - Print for %s (no rbp func)
;-------------------------------------------
; Entry:        r14 - ptr to ptr string
;
; Expects:      [rbp + hConsoleOutputOffset] = hConsoleOutput
;
; Exit:         None
;
; Destroys:     rax rcx rdx r8 r9
;-------------------------------------------
; Stack frame:
;               ...
;               retAddr     [...]
;               ...
;-------------------------------------------
section .text
printS:
        push r12
        mov r12, [r14]
        add r14, 8

        jmp .ScanBeginning              ;               >>>>>>>>>>>>>>>>
        .OneChar:                       ; <---------------------\
                nop                     ;                       |
                call printChar          ;                       |
                                        ;                       |
                inc r12                 ;                       |
            .ScanBeginning:             ;               <<<<<<<<<<<<<<<<
                mov bl, [r12]           ; bl = next character   |
                test bl, bl             ;                       |
                jnz .OneChar            ; >---------------------/

        pop r12
        ret
;-------------------------------------------
;-------------------------------------------


;-------------------------------------------
; printC - Print for %c (no rbp func)
;-------------------------------------------
; Entry:        r14 - ptr value
;
; Expects:      [rbp + hConsoleOutputOffset] = hConsoleOutput
;
; Exit:         None
;
; Destroys:     rax rcx rdx r8 r9
;-------------------------------------------
; Stack frame:
;               ...
;               retAddr     [...]
;               ...
;-------------------------------------------
section .text
printC:
        push r12
        mov r12, r14
        add r14, 8

        call printChar

        pop r12
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
; Buffers
;-------------------------------------------
section .bss

SignBuffer      dq ?
DigitBuffer     db 64 dup(?)


;-------------------------------------------
; Constants
;-------------------------------------------
section .data

STD_OUTPUT_HANDLE equ (-11)

; MASK_SIGN       equ -0x8000000000000000
; MASK_POSITIVE   equ  0x7fffffffffffffff

MASK_B          equ 1
MASK_O          equ 7
MASK_X          equ 15
DIGIT_COUNT_B   equ 64
DIGIT_COUNT_O   equ 24 ; 22 -> 24
DIGIT_COUNT_X   equ 16
DIGIT_COUNT_D   equ 24
SHR_COUNT_B     equ 1
SHR_COUNT_O     equ 3
SHR_COUNT_X     equ 4
DIV_BASE_D      equ 10
MASK_32BIT      equ (0ffffffffh)

        ; Mode table:
        ;        value  | mode
        ;       --------+---------------
        ;          0    | normal
        ;          1    | character after %

ModeNormal      equ 0
ModeProcent     equ 1

HexAlphabet     db "0123456789abcdef"
MinusAlpha      db "-"

ModeCallTable   dq ..@ModeNormal
                dq ..@ModeProcent

ProcentCallTable dq printB      ; b
                dq printC       ; c
                dq printD       ; d
                dq 7 dup(printChar)
                dq printL       ; l
                dq 2 dup(printChar)
                dq printO       ; o
                dq 3 dup(printChar)
                dq printS       ; s
                dq 4 dup(printChar)
                dq printX       ; x

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
