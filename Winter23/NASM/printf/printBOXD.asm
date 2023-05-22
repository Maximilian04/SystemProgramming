;===========================================
;   printBOXD.asm
;   NASM printf implication
;===========================================


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
                ; add al, "0"             ;                     |
                mov al, [HexAlphabet + rax];                    |
                                        ;                       |
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
