;===========================================
;   callPrintfm.asm
;   NASM printf implication
;===========================================

;-------------------------------------------
; External stuff
;-------------------------------------------

extern printfm


;-------------------------------------------
; callPrintf - Asm printf caller
;-------------------------------------------
; Entry:        1st     (RCX)   format
;               variable number of parameters
;-------------------------------------------
;
; Expects:      
;
; Exit:         None
;
; Destroys:     rax rcx rdx r8 r9
;-------------------------------------------
; Stack frame:
;               ...         [ ...    ]
;               - (4st)     [rsp + 32]
;               - (3st)     [rsp + 24]
;               - (2nd)     [rsp + 16]
;               - (1st)     [rsp + 8]
;               retAddr     [rsp]
;               ...
;-------------------------------------------
section .text
global callPrintfm
callPrintfm:

        mov rax,   [rsp +  0]
        mov [SavedStack +  0], rax
        mov rax,   [rsp +  8]
        mov [SavedStack +  8], rax
        mov rax,   [rsp + 16]
        mov [SavedStack + 16], rax
        mov rax,   [rsp + 24]
        mov [SavedStack + 24], rax
        mov rax,   [rsp + 32]
        mov [SavedStack + 32], rax
        ; Save all info that will be erased


        mov [SavedStack +  8], rcx
        mov [SavedStack + 16], rdx
        mov [SavedStack + 24], r8
        mov [SavedStack + 32], r9
        add rsp, 8
        call printfm
        sub rsp, 8

        
        ; Restore all erased info
        mov rax, [SavedStack +  0]
        mov             [rsp +  0], rax
        mov rax, [SavedStack +  8]
        mov             [rsp +  8], rax
        mov rax, [SavedStack + 16]
        mov             [rsp + 16], rax
        mov rax, [SavedStack + 24]
        mov             [rsp + 24], rax
        mov rax, [SavedStack + 32]
        mov             [rsp + 32], rax

        ret
;-------------------------------------------
;-------------------------------------------


;-------------------------------------------
; Stored data
;-------------------------------------------
section .bss

SavedStack      dq 5 dup(?)


;-------------------------------------------
; x64 c calling convention
;
;       1st     RCX
;       2nd     RDX	
;	3rd     R8	
;	4th     R9
;       5th+    to stack
;-------------------------------------------
