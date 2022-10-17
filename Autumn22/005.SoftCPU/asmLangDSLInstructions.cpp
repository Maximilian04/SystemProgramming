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
    return Error::OK_HALT;
    }
)
DESCRIPT_COMMAND("push", 0x01,
    {
    stack::push(&mainCPU->stack, commandArgs.argSum);
    }
)
DESCRIPT_COMMAND("add", 0x02, {
    AsmCode_t a = 0;
    AsmCode_t b = 0;
    stack::pop(&mainCPU->stack, &b);
    stack::pop(&mainCPU->stack, &a);
    stack::push(&mainCPU->stack, (AsmCode_t)(a + b));
    }
)
DESCRIPT_COMMAND("div", 0x03, {
    AsmCode_t a = 0;
    AsmCode_t b = 0;
    stack::pop(&mainCPU->stack, &b);
    stack::pop(&mainCPU->stack, &a);
    stack::push(&mainCPU->stack, a / b);
    }
)
DESCRIPT_COMMAND("out", 0x04, {
    AsmCode_t a = 0;
    stack::pop(&mainCPU->stack, &a);
    printf("%u\n", a);
    }
)
DESCRIPT_COMMAND("pop", 0x05, {
    stack::pop(&mainCPU->stack, commandArgs.argWritePtr);
    }
)
DESCRIPT_COMMAND("jump", 0x06, {
    mainCPU->code.pc = commandArgs.argSum;
    }
)