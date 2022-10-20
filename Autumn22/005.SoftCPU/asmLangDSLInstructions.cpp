/**
 * @file asmLangDSLInstructions.cpp
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Instructions for mAsm language behaviour. File need to be included wherever you want to use command instructions.
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

DESCRIPT_COMMAND("hlt", 0x00, {
    HAULT;
    }
)
DESCRIPT_COMMAND("out", 0x01, {
    GET_VAR(a);
    printf("%u\n", a);
    }
)
DESCRIPT_COMMAND("in", 0x02, {
    VAR(a);
    int b = 0;
    scanf("%d", &b);
    a = TO_ASM_TYPE(b);
    PUSH(a);
    }
)
DESCRIPT_COMMAND("push", 0x03, {
    PUSH(commandArgs.argSum);
    }
)
DESCRIPT_COMMAND("pop", 0x04, {
    POP(commandArgs.argWritePtr);
    }
)
DESCRIPT_COMMAND("jmp", 0x05, {
    CHANGE_PC;
    }
)

#define GET_ARITHMETIC_ARGS \
    GET_VAR(b);              \
    GET_VAR(a);

#define DESCRIPT_JMP_COMMAND(name, bytecode, _) \
DESCRIPT_COMMAND(name, bytecode, {               \
    GET_ARITHMETIC_ARGS                           \
    if (a _ b) {                                   \
        CHANGE_PC;                                  \
        }                                            \
    }                                                 \
)

DESCRIPT_JMP_COMMAND("ja",  0x06, >  )
DESCRIPT_JMP_COMMAND("jae", 0x07, >= )
DESCRIPT_JMP_COMMAND("jb",  0x08, <  )
DESCRIPT_JMP_COMMAND("jbe", 0x09, <= )
DESCRIPT_JMP_COMMAND("je",  0x0A, == )
DESCRIPT_JMP_COMMAND("jne", 0x0B, != )
#undef DESCRIPT_JMP_COMMAND


DESCRIPT_COMMAND("call", 0x0C, {
    PUSH_FUNCSTACK(mainCPU->code.pc);
    CHANGE_PC;
    }
)
DESCRIPT_COMMAND("ret", 0x0D, {
    VAR(a);
    POP_FUNCSTACK(&a);
    SET_PC(a);
    }
)
DESCRIPT_COMMAND("add", 0x0E, {
    GET_ARITHMETIC_ARGS
    PUSH(TO_ASM_TYPE(a + b));
    }
)
DESCRIPT_COMMAND("sub", 0x0F, {
    GET_ARITHMETIC_ARGS
    PUSH(TO_ASM_TYPE(a - b));
    }
)
DESCRIPT_COMMAND("mul", 0x10, {
    GET_ARITHMETIC_ARGS
    PUSH(a * b);
    }
)
DESCRIPT_COMMAND("div", 0x11, {
    GET_ARITHMETIC_ARGS
    PUSH(a / b);
    }
)
DESCRIPT_COMMAND("dump", 0x12, {
    cpu::dump(&(*mainCPU), __PRETTY_FUNCTION__, "./..\\asmLangDSLInstructions.cpp", 96);
    }
)
#undef GET_ARITHMETIC_ARGS
