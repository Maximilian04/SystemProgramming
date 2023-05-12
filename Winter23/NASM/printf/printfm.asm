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
;               2st         [rbp + 32] // printf arg
;               1st         [rbp + 16] // format string ptr
;               retAddr     [rbp + 8]
;               stored BP   [rbp]
;               stored rbx  [rbp - 8]
;            hConsoleOutput [rbp - 16]
;               ...
;-------------------------------------------
section .text
global printfm
printfm:
        push rbp
        mov rbp, rsp                    ; Stack frame
        push rbx                        ; store external rbx to stack


        mov rcx, STD_OUTPUT_HANDLE      ; STD_OUTPUT_HANDLE = -11
        call GetStdHandle               ; rax = hConsoleOutput = GetStdHandle(-11)

        push rax                        ; hConsoleOutput -> stack


        mov rbx, [rbp + 16]             ; format string ptr -> rbx


        .OneChar:                       ; <---------------------\
                                        ;                       |
                                        ;                       |
                mov rcx, [rbp - 16]     ; hConsoleOutput        |
                mov rdx, rbx            ; string ptr            |
                mov r8, 1               ; one character         |
                mov r9, 0               ;                       |
                push qword 0            ;                       |
                call WriteConsoleA      ; WriteConsole  (hConsoleOutput, ptr, 1, 0, 0)
                pop rax                 ;                       |
                                        ;                       |
                                        ;                       |
                                        ;                       |
                inc rbx                 ;                       |
                mov al, [rbx]           ;                       |
                test al, al             ;                       |
                jnz .OneChar            ; >---------------------/


        pop rax                         ; remove hConsoleOutput

        pop rbx                         ; restore external rbx
        pop rbp
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

;-------------------------------------------
;-------------------------------------------
; ld hello.obj "C:\Windows\System32\kernel32.dll" "C:\Windows\System32\user32.dll" -e __start
;       or
; nasm printfm.asm -f win64
;-------------------------------------------
;-------------------------------------------
