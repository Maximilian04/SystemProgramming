;===========================================
;   printf.asm
;   NASM printf implication and call for c-function
;===========================================

;-------------------------------------------
; External stuff
;-------------------------------------------

extern GetStdHandle                     ; kernel32.dll
extern WriteConsoleA                    ; kernel32.dll
extern ExitProcess                      ; kernel32.dll
extern MessageBoxA                      ; user32.dll

extern printf                           ; -.dll

section .text

;-------------------------------------------
; Main program with functions callings
;-------------------------------------------
global asmFunction
asmFunction:
                push rbx                ; store external rbx to stack


                mov rcx, STD_OUTPUT_HANDLE; STD_OUTPUT_HANDLE = -11
                call GetStdHandle       ; rax = hConsoleOutput = GetStdHandle(-11)

                mov rbx, rax            ; store hConsoleOutput -> rbx


                mov rcx, rbx            ; hConsoleOutput
                mov rdx, MsgText
                mov r8, MsgTextLength
                mov r9, 0
                sub rsp, (8*4)
                push qword 0
                call WriteConsoleA      ; WriteConsole (hConsoleOutput, msg, length, 0, 0)
                add rsp, (8*5)


                mov rcx, MsgPrintf
                mov rdx, 7
                mov r8, MsgText2
                mov r9, rsp
                sub rsp, (8*4)
                push qword 775
                call printf             ; printf (MsgPrintf, 7, MsgText2, rsp, 775)
                add rsp, (8*5)


                push MsgPrintf2
                call myPrintf
                pop rax


                pop rbx                 ; restore external rbx

                ret
                ; mov rcx, 0
                ; call ExitProcess        ; ExitProcess (0)
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
; My printf
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
; global myPrintf
myPrintf:
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
; Printf caller
;-------------------------------------------
; Entry:        DI = start addr to draw
;               CX = width of line (without A&C)
;
; Expects:      
;
; Exit:         None
;
; Destroys:     RCX (1st param)
;               RDX (2st param)
;               R8  (3st param)
;               R9  (4st param)
;               following via stack
;-------------------------------------------
; Stack frame:
;               ...
;               'A' char    [rbp + 8]    // H - color attr
;               'B' char    [rbp + 6]    // L - symb attr
;               'C' char    [rbp + 4]    //
;               retAddr     [rbp + 2]
;               stored BP   [rbp]
;               ...
;-------------------------------------------
global callPrintf
callPrintf:
        push rbp
        mov rbp, rsp                    ; Stack frame


        ; mov     rdi, format             ; set 1st parameter (format)
        ; mov     rsi, rax                ; set 2nd parameter (current_number)
        ; xor     rax, rax                ; because printf is varargs

        ; ? Stack is already aligned because we pushed three 8 byte registers
        ; call    printf                  ; printf(format, current_number)


        ; mov     rdx, rax                ; save the current number
        ; mov     rax, rbx                ; next number is now current
        ; add     rbx, rdx                ; get the new next number
        ; dec     ecx                     ; count down
        ; jnz     print                   ; if not done counting, do some more

        ; pop     rbx                     ; restore rbx before returning
        pop rbp
        ret
;-------------------------------------------
;-------------------------------------------

section .data

MsgTitle        db "Title", 0ah, 0
MsgText         db "This function was written with asm", 0ah
MsgTextLength   equ ($ - MsgText)
MsgText2        db "Noooo", 0
MsgText3        db "Yess", 0ah, 0

MsgPrintf       db "Ququququ %d'%s' qwe rsp:%d,%d", 0ah, 0
MsgPrintf2      db "KUKUKUuu %d'%s' qwe rsp:%d,%d", 0ah, 0

STD_OUTPUT_HANDLE equ (-11)

;-------------------------------------------
;-------------------------------------------
; ld hello.obj "C:\Windows\System32\kernel32.dll" "C:\Windows\System32\user32.dll" -e __start
;       or
; nasm printfm.asm -f win64
;-------------------------------------------
;-------------------------------------------
