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
; printB - Print for %b
;-------------------------------------------
; Entry:        r14 - ptr to value
;
; Expects:      [rbp + hConsoleOutputOffset] = hConsoleOutput
;
; Exit:         None
;
; Destroys:     
;-------------------------------------------
; Stack frame:
;               ...
;               retAddr     [rbp + 8]
;               stored BP   [rbp]
;            hConsoleOutput [rbp - 8]
;               stored rax  [rbp - 16]
;               stored rbx  [rbp - 24]
;               stored rcx  [rbp - 32]
;               stored rdx  [rbp - 40]
;               stored r8   [rbp - 48]
;               stored r9   [rbp - 56]
;               stored r12  [rbp - 64]
;               stored r13  [rbp - 72]
;               stored r14  [rbp - 80]
;               stored r15  [rbp - 88]
;-------------------------------------------
section .text
printB:
        push rbp
        mov rbp, rsp                    ; Stack frame
        push qword 0                    ; space for hConsoleOutput
        push rax                        ; store external rax to stack
        push rbx                        ; store external rbx to stack
        push rcx                        ; store external rcx to stack
        push rdx                        ; store external rdx to stack
        push r8                         ; store external r8  to stack
        push r9                         ; store external r9  to stack
        push r12                        ; store external r12 to stack
        push r13                        ; store external r13 to stack
        push r14                        ; store external r14 to stack
        push r15                        ; store external r15 to stack

        mov rax, [rbp]
        mov rax, [rax + hConsoleOutputOffset]
        mov [rbp + hConsoleOutputOffset], rax


        mov r12, DigitBuffer
        mov r13, [r14]                  ; r13 = value
        mov rbx, DIGIT_COUNT_B

        mov r15, DIGIT_COUNT_B          ; r15 = last not zero index (from rbx)


        ; printChar destroys rax rcx rdx r8 r9

        .GetDigit:                      ; <---------------------\
                nop                     ;                       |
                mov rax, r13            ;                       |
                shr r13, SHR_COUNT_B    ;                       |
                                        ;                       |
                and rax, MASK_B         ;                       |
                jz .Zero                ; >>====\\              |
                mov r15, rbx            ;       ||              |
                                        ;       ||              |
            .Zero:                      ; <<====//              |
                add al, "0"             ;                       |
                mov [r12], al           ;                       |
                                        ;                       |
                add r12, 1              ;                       |
                dec rbx                 ;                       |
                test rbx, rbx           ;                       |
                jnz .GetDigit           ; >---------------------/

        mov rbx, DIGIT_COUNT_B + 1
        sub rbx, r15
        sub r12, r15
        .OneDigit:                      ; <---------------------\
                                        ;                       |
                call printChar          ;                       |
                                        ;                       |
                sub r12, 1              ;                       |
                                        ;                       |
                dec rbx                 ;                       |
                test rbx, rbx           ;                       |
                jnz .OneDigit           ; >---------------------/


        pop r15                         ; restore external r15
        pop r14                         ; restore external r14
        add r14, 8                      ; next vararg
        pop r13                         ; restore external r13
        pop r12                         ; restore external r12
        pop r9                          ; restore external r9
        pop r8                          ; restore external r8
        pop rdx                         ; restore external rdx
        pop rcx                         ; restore external rcx
        pop rbx                         ; restore external rbx
        pop rax                         ; restore external rax
        add rsp, 8                      ; remove hConsoleOutput
        pop rbp
        ret
;-------------------------------------------
;-------------------------------------------


;-------------------------------------------
; printO - Print for %o
;-------------------------------------------
; Entry:        r14 - ptr to value
;
; Expects:      [rbp + hConsoleOutputOffset] = hConsoleOutput
;
; Exit:         None
;
; Destroys:     
;-------------------------------------------
; Stack frame:
;               ...
;               retAddr     [rbp + 8]
;               stored BP   [rbp]
;            hConsoleOutput [rbp - 8]
;               stored rax  [rbp - 16]
;               stored rbx  [rbp - 24]
;               stored rcx  [rbp - 32]
;               stored rdx  [rbp - 40]
;               stored r8   [rbp - 48]
;               stored r9   [rbp - 56]
;               stored r12  [rbp - 64]
;               stored r13  [rbp - 72]
;               stored r14  [rbp - 80]
;               stored r15  [rbp - 88]
;-------------------------------------------
section .text
printO:
        push rbp
        mov rbp, rsp                    ; Stack frame
        push qword 0                    ; space for hConsoleOutput
        push rax                        ; store external rax to stack
        push rbx                        ; store external rbx to stack
        push rcx                        ; store external rcx to stack
        push rdx                        ; store external rdx to stack
        push r8                         ; store external r8  to stack
        push r9                         ; store external r9  to stack
        push r12                        ; store external r12 to stack
        push r13                        ; store external r13 to stack
        push r14                        ; store external r14 to stack
        push r15                        ; store external r15 to stack

        mov rax, [rbp]
        mov rax, [rax + hConsoleOutputOffset]
        mov [rbp + hConsoleOutputOffset], rax


        mov r12, DigitBuffer
        mov r13, [r14]                  ; r13 = value
        mov rbx, DIGIT_COUNT_O

        mov r15, DIGIT_COUNT_O          ; r15 = last not zero index (from rbx)


        ; printChar destroys rax rcx rdx r8 r9

        .GetDigit:                      ; <---------------------\
                nop                     ;                       |
                mov rax, r13            ;                       |
                shr r13, SHR_COUNT_O    ;                       |
                                        ;                       |
                and rax, MASK_O         ;                       |
                jz .Zero                ; >>====\\              |
                mov r15, rbx            ;       ||              |
                                        ;       ||              |
            .Zero:                      ; <<====//              |
                add al, "0"             ;                       |
                mov [r12], al           ;                       |
                                        ;                       |
                add r12, 1              ;                       |
                dec rbx                 ;                       |
                test rbx, rbx           ;                       |
                jnz .GetDigit           ; >---------------------/

        mov rbx, DIGIT_COUNT_O + 1
        sub rbx, r15
        sub r12, r15
        .OneDigit:                      ; <---------------------\
                                        ;                       |
                call printChar          ;                       |
                                        ;                       |
                sub r12, 1              ;                       |
                                        ;                       |
                dec rbx                 ;                       |
                test rbx, rbx           ;                       |
                jnz .OneDigit           ; >---------------------/


        pop r15                         ; restore external r15
        pop r14                         ; restore external r14
        add r14, 8                      ; next vararg
        pop r13                         ; restore external r13
        pop r12                         ; restore external r12
        pop r9                          ; restore external r9
        pop r8                          ; restore external r8
        pop rdx                         ; restore external rdx
        pop rcx                         ; restore external rcx
        pop rbx                         ; restore external rbx
        pop rax                         ; restore external rax
        add rsp, 8                      ; remove hConsoleOutput
        pop rbp
        ret
;-------------------------------------------
;-------------------------------------------


;-------------------------------------------
; printX - Print for %x
;-------------------------------------------
; Entry:        r14 - ptr to value
;
; Expects:      [rbp + hConsoleOutputOffset] = hConsoleOutput
;
; Exit:         None
;
; Destroys:     
;-------------------------------------------
; Stack frame:
;               ...
;               retAddr     [rbp + 8]
;               stored BP   [rbp]
;            hConsoleOutput [rbp - 8]
;               stored rax  [rbp - 16]
;               stored rbx  [rbp - 24]
;               stored rcx  [rbp - 32]
;               stored rdx  [rbp - 40]
;               stored r8   [rbp - 48]
;               stored r9   [rbp - 56]
;               stored r12  [rbp - 64]
;               stored r13  [rbp - 72]
;               stored r14  [rbp - 80]
;               stored r15  [rbp - 88]
;-------------------------------------------
section .text
printX:
        push rbp
        mov rbp, rsp                    ; Stack frame
        push qword 0                    ; space for hConsoleOutput
        push rax                        ; store external rax to stack
        push rbx                        ; store external rbx to stack
        push rcx                        ; store external rcx to stack
        push rdx                        ; store external rdx to stack
        push r8                         ; store external r8  to stack
        push r9                         ; store external r9  to stack
        push r12                        ; store external r12 to stack
        push r13                        ; store external r13 to stack
        push r14                        ; store external r14 to stack
        push r15                        ; store external r15 to stack

        mov rax, [rbp]
        mov rax, [rax + hConsoleOutputOffset]
        mov [rbp + hConsoleOutputOffset], rax


        mov r12, DigitBuffer
        mov r13, [r14]                  ; r13 = value
        mov rbx, DIGIT_COUNT_X

        mov r15, DIGIT_COUNT_X          ; r15 = last not zero index (from rbx)


        ; printChar destroys rax rcx rdx r8 r9

        .GetDigit:                      ; <---------------------\
                nop                     ;                       |
                mov rax, r13            ;                       |
                shr r13, SHR_COUNT_X    ;                       |
                                        ;                       |
                and rax, MASK_X         ;                       |
                jz .Zero                ; >>====\\              |
                mov r15, rbx            ;       ||              |
                                        ;       ||              |
            .Zero:                      ; <<====//              |
                add al, "0"             ;                       |
                mov [r12], al           ;                       |
                                        ;                       |
                add r12, 1              ;                       |
                dec rbx                 ;                       |
                test rbx, rbx           ;                       |
                jnz .GetDigit           ; >---------------------/

        mov rbx, DIGIT_COUNT_X + 1
        sub rbx, r15
        sub r12, r15
        .OneDigit:                      ; <---------------------\
                                        ;                       |
                call printChar          ;                       |
                                        ;                       |
                sub r12, 1              ;                       |
                                        ;                       |
                dec rbx                 ;                       |
                test rbx, rbx           ;                       |
                jnz .OneDigit           ; >---------------------/


        pop r15                         ; restore external r15
        pop r14                         ; restore external r14
        add r14, 8                      ; next vararg
        pop r13                         ; restore external r13
        pop r12                         ; restore external r12
        pop r9                          ; restore external r9
        pop r8                          ; restore external r8
        pop rdx                         ; restore external rdx
        pop rcx                         ; restore external rcx
        pop rbx                         ; restore external rbx
        pop rax                         ; restore external rax
        add rsp, 8                      ; remove hConsoleOutput
        pop rbp
        ret
;-------------------------------------------
;-------------------------------------------


;-------------------------------------------
; printD - Print for %d
;-------------------------------------------
; Entry:        r14 - ptr to value
;
; Expects:      [rbp + hConsoleOutputOffset] = hConsoleOutput
;
; Exit:         None
;
; Destroys:     
;-------------------------------------------
; Stack frame:
;               ...
;               retAddr     [rbp + 8]
;               stored BP   [rbp]
;            hConsoleOutput [rbp - 8]
;               stored rax  [rbp - 16]
;               stored rbx  [rbp - 24]
;               stored rcx  [rbp - 32]
;               stored rdx  [rbp - 40]
;               stored r8   [rbp - 48]
;               stored r9   [rbp - 56]
;               stored r12  [rbp - 64]
;               stored r13  [rbp - 72]
;               stored r14  [rbp - 80]
;               stored r15  [rbp - 88]
;-------------------------------------------
section .text
printD:
        push rbp
        mov rbp, rsp                    ; Stack frame
        push qword 0                    ; space for hConsoleOutput
        push rax                        ; store external rax to stack
        push rbx                        ; store external rbx to stack
        push rcx                        ; store external rcx to stack
        push rdx                        ; store external rdx to stack
        push r8                         ; store external r8  to stack
        push r9                         ; store external r9  to stack
        push r12                        ; store external r12 to stack
        push r13                        ; store external r13 to stack
        push r14                        ; store external r14 to stack
        push r15                        ; store external r15 to stack

        mov rax, [rbp]
        mov rax, [rax + hConsoleOutputOffset]
        mov [rbp + hConsoleOutputOffset], rax


        mov r12, DigitBuffer
        mov r13, [r14]                  ; r13 = value
        mov rbx, DIGIT_COUNT_D

        mov r15, DIGIT_COUNT_D          ; r15 = last not zero index (from rbx)

        ; division:   {rdx|rax}/m64 = rax (остаток rdx)
        ; division:   {    rax}/m8  = al  (остаток ah)
        ; printChar destroys rax rcx rdx r8 r9

        .GetDigit:                      ; <---------------------\
                nop                     ;                       |
                mov rax, r13            ;                       |
                ; shr r13, SHR_COUNT_X  ;                       |
                mov rdx, 0              ;                       |
                mov r13, DIV_BASE_D     ;                       |
                div r13                 ; rax = r13/10          |
                                        ; rdx = r13%10          |
                mov r13, rax            ;                       |
                mov rax, rdx            ;                       |
                ; and rax, MASK_D       ;                       |
                test rax, rax           ;                       |
                jz .Zero                ; >>====\\              |
                mov r15, rbx            ;       ||              |
                                        ;       ||              |
            .Zero:                      ; <<====//              |
                add al, "0"             ;                       |
                mov [r12], al           ;                       |
                                        ;                       |
                add r12, 1              ;                       |
                dec rbx                 ;                       |
                test rbx, rbx           ;                       |
                jnz .GetDigit           ; >---------------------/

        mov rbx, DIGIT_COUNT_D + 1
        sub rbx, r15
        sub r12, r15
        .OneDigit:                      ; <---------------------\
                                        ;                       |
                call printChar          ;                       |
                                        ;                       |
                sub r12, 1              ;                       |
                                        ;                       |
                dec rbx                 ;                       |
                test rbx, rbx           ;                       |
                jnz .OneDigit           ; >---------------------/


        pop r15                         ; restore external r15
        pop r14                         ; restore external r14
        add r14, 8                      ; next vararg
        pop r13                         ; restore external r13
        pop r12                         ; restore external r12
        pop r9                          ; restore external r9
        pop r8                          ; restore external r8
        pop rdx                         ; restore external rdx
        pop rcx                         ; restore external rcx
        pop rbx                         ; restore external rbx
        pop rax                         ; restore external rax
        add rsp, 8                      ; remove hConsoleOutput
        pop rbp
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

DigitBuffer     db 64 dup(?)


;-------------------------------------------
; Constants
;-------------------------------------------
section .data

STD_OUTPUT_HANDLE equ (-11)

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

        ; Mode table:
        ;        value  | mode
        ;       --------+---------------
        ;          0    | normal
        ;          1    | character after %

ModeNormal      equ 0
ModeProcent     equ 1

ModeCallTable   dq ..@ModeNormal
                dq ..@ModeProcent

ProcentCallTable dq printB      ; b
                dq printC       ; c
                dq printD       ; d
                dq 10 dup(printChar)
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
