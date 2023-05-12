;===========================================
;   asmMain.asm
;   printfm & printf caller
;===========================================

;-------------------------------------------
; External stuff
;-------------------------------------------

extern printf                           ; stl

extern printfm


;-------------------------------------------
; Main program with functions callings
;-------------------------------------------
section .text
global asmMain
asmMain:
                push rbx                ; store external rbx to stack


                mov rcx, MsgPrintf
                mov rdx, 7
                mov r8, MsgText2
                mov r9, rsp
                sub rsp, (8*4)
                push qword 775
                call printf             ; printf (MsgPrintf, 7, MsgText2, rsp, 775)
                add rsp, (8*5)


                push qword 775
                push qword rsp
                push qword MsgText2
                ; push qword 7
                push qword MsgPrintf2
                call printfm
                add rsp, (8*4)


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

MsgPrintf       db "Ququququ %d'%s' qwe%% rsp:%d,%d", 0ah, 0
MsgPrintf2      db "KUKUKUuu %d'%s' qwe%% rsp:%d,%d", 0ah, 0

STD_OUTPUT_HANDLE equ (-11)

;-------------------------------------------
;-------------------------------------------
; ld hello.obj "C:\Windows\System32\kernel32.dll" "C:\Windows\System32\user32.dll" -e __start
;       or
; nasm printfm.asm -f win64
;-------------------------------------------
;-------------------------------------------
