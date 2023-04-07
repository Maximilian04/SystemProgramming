;===========================================
;   hello.asm
;   NASM example
;===========================================

; nasm    "1-Nasm+Ld.asm" -f win32 -l "1-Nasm+Ld.lst"
; ld      "1-Nasm+Ld.obj" -o "1-Nasm+Ld.exe" libkernel32.a libuser32.a -e __start

;nasm hello.asm -f win64
;ld hello.obj "C:\Windows\System32\kernel32.dll" "C:\Windows\System32\user32.dll"

global __start

extern GetStdHandle                  ; kernel32.dll
extern WriteConsoleA                ; kernel32.dll
extern ExitProcess                   ; kernel32.dll
extern MessageBoxA                  ; user32.dll


section .text


section .text


__start:        
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
                call ExitProcess        ; ExitProcess (0)

section .data

MsgTitle        db "Title", 0ah, 0
MsgText         db "Text", 0ah
MsgText2        db "Noooo", 0
MsgText3        db "Yess",  0ah, 0
