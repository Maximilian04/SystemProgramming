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
                mov rdx, StringPrintf
                mov r8, 775
                mov r9, 776

                push qword 778
                push qword 777
                sub rsp, (8*4)
                call printf             ; printf (MsgPrintf, 7, MsgText2, rsp, 775)
                add rsp, (8*6)


                push qword 778
                push qword 777
                push qword 776
                push qword 775
                push qword StringPrintf
                push qword MsgPrintf
                call printfm
                add rsp, (8*6)


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

; MsgPrintf       db "Ququququ '%s'%x|%d qwe%% rsp:%d,%d,%b,%d,%d", 0ah, 0
; MsgPrintf2      db "KUKUKUuu '%s'%x|%d qwe%% rsp:%d,%d,%b", 0ah, 0

MsgPrintfSimple db "Ququ string:'%s', dec:%d, dec:%d, dec:%d, dec:%d~", 0ah, 0
MsgPrintf       db "Ququ string:'%s', hex:%x, oct:%o, bin:%b, dec:%d~", 0ah, 0
StringPrintf    db "Yeaa", 0

STD_OUTPUT_HANDLE equ (-11)

;-------------------------------------------
;-------------------------------------------
; ld hello.obj "C:\Windows\System32\kernel32.dll" "C:\Windows\System32\user32.dll" -e __start
;       or
; nasm printfm.asm -f win64
;-------------------------------------------
;-------------------------------------------
