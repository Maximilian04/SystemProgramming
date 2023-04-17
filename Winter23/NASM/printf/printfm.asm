;===========================================
;   hello.asm
;   NASM example
;===========================================

; nasm    "1-Nasm+Ld.asm" -f win32 -l "1-Nasm+Ld.lst"
; ld      "1-Nasm+Ld.obj" -o "1-Nasm+Ld.exe" libkernel32.a libuser32.a -e __start

;nasm hello.asm -f win64
;ld hello.obj "C:\Windows\System32\kernel32.dll" "C:\Windows\System32\user32.dll"

;-------------------------------------------
; External stuff
;-------------------------------------------

; global __start

extern GetStdHandle                     ; kernel32.dll
extern WriteConsoleA                    ; kernel32.dll
extern ExitProcess                      ; kernel32.dll
extern MessageBoxA                      ; user32.dll

global asmFunction

section .text

;-------------------------------------------
; Main program
;-------------------------------------------

asmFunction:
                push rbx

                mov rcx, -11            ; STD_OUTPUT_HANDLE = -11
                call GetStdHandle       ; stdout = GetStdHandle(-11)
                                        ; rax = stdout

                mov rbx, rax

                mov rcx, 0
                mov rdx, MsgText
                mov r8, MsgTitle
                mov r9, 0
                call MessageBoxA    ; MessageBoxA (NULL, MsgText, MsgTitle, 0)

                mov rcx, rbx            ; hConsoleOutput
                mov rdx, MsgText
                mov r8, 5
                mov r9, 0
                push qword 0
                call WriteConsoleA  ; WriteConsole (stdout, msg, 5, 0, 0)
                pop rax

                mov rcx, rbx            ; hConsoleOutput
                mov rdx, MsgText3
                mov r8, 5
                mov r9, 0
                push qword 0
                call WriteConsoleA  ; WriteConsole (stdout, msg, 5, 0, 0)
                pop rax

                mov rcx, rbx            ; hConsoleOutput
                mov rdx, MsgText2
                mov r8, 4
                mov r9, 0
                push qword 0
                call WriteConsoleA  ; WriteConsole (stdout, msg, 5, 0, 0)
                pop rax



                pop rbx

                mov rcx, 0
                ret

                ; call ExitProcess        ; ExitProcess (0)


;-------------------------------------------
; Printf caller
;-------------------------------------------
; Entry:        DI = start addr to draw
;               CX = width of line (without A&C)
;
; Expects:      ES -> Video segment
;               DF = 0 (CLD)
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

section .data

MsgTitle        db "Title", 0ah, 0
MsgText         db "Text", 0ah
MsgText2        db "Noooo", 0
MsgText3        db "Yess",  0ah, 0
