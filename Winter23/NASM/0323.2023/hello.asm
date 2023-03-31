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
 
_start:
    ; At _start the stack is 8 bytes misaligned because there is a return
    ; address to the MSVCRT runtime library on the stack.
    ; 8 bytes of temporary storage for `bytes`.
    ; allocate 32 bytes of stack for shadow space.
    ; 8 bytes for the 5th parameter of WriteConsole.
    ; An additional 8 bytes for padding to make RSP 16 byte aligned.
    sub     rsp, 8+8+8+32
    ; At this point RSP is aligned on a 16 byte boundary and all necessary
    ; space has been allocated.
 
    ; hStdOut = GetStdHandle(STD_OUTPUT_HANDLE)
    mov     ecx, -11
    call    GetStdHandle
 
    ; WriteFile(hstdOut, message, length(message), &bytes, 0);
    mov     rcx, rax
    mov     rdx, MsgText
    mov     r8,  5
    lea     r9,  [rsp-16]         ; Address for `bytes`
    ; RSP-17 through RSP-48 are the 32 bytes of shadow space
    mov     qword [rsp-56], 0     ; First stack parameter of WriteConsoleA function
    call    WriteConsoleA
 
    ; ExitProcess(0)
    ;    mov     rcx, 0
    ;    call    ExitProcess
 
    ; alternatively you can exit by setting RAX to 0
    ; and doing a ret
 
    add rsp, 8+8+32+8             ; Restore the stack pointer.
    xor eax, eax                  ; RAX = return value = 0
    ret


__start:        
                push rbx

                mov rcx, -11            ; STD_OUTPUT_HANDLE = -11
                call GetStdHandle       ; stdout = GetStdHandle(-11)
                                        ; rax = stdout

                mov rbx, rax

                mov rcx, rax            ; hConsoleOutput
                mov rdx, MsgText
                mov r8, 4
                mov r9, 0
                push qword 0
                call WriteConsoleA  ; WriteConsole (stdout, msg, 5, 0, 0)
                pop rax

                mov rcx, rbx            ; hConsoleOutput
                mov rdx, MsgText2
                mov r8, 5
                mov r9, 4
                push qword 0
                call WriteConsoleA  ; WriteConsole (stdout, msg, 5, 0, 0)
                pop rax

                mov rcx, rbx            ; hConsoleOutput
                mov rdx, MsgText3
                mov r8, 5
                mov r9, 9
                push qword 0
                call WriteConsoleA  ; WriteConsole (stdout, msg, 5, 0, 0)
                pop rax

                mov rcx, rbx
                mov rdx, MsgText
                mov r8, MsgTitle
                mov r9, 0
                call MessageBoxA    ; MessageBoxA (NULL, MsgText, MsgTitle, 0)

                pop rbx

                mov rcx, 0
                call ExitProcess        ; ExitProcess (0)

section .data

MsgTitle        db "Title", 0ah, 0
MsgText         db "Text", 0
MsgText2        db "Nooo",  'x', 0
MsgText3        db "Yess",  0ah, 0
