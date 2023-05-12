;===========================================
;   asmMain.asm
;   printfm & printf caller
;===========================================

;-------------------------------------------
; External stuff
;-------------------------------------------

extern GetStdHandle                     ; kernel32.dll
extern WriteConsoleA                    ; kernel32.dll
extern ExitProcess                      ; kernel32.dll
extern MessageBoxA                      ; user32.dll

extern printf                           ; stl

extern printfm


;-------------------------------------------
; Main program with functions callings
;-------------------------------------------
section .text
global asmMain
asmMain:
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
                call printfm
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
;	    3rd     R8	
;	    4th     R9
;       5th+    to stack
;-------------------------------------------


;-------------------------------------------
; Constants
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
