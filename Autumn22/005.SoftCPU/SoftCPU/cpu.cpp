#include <..\asmLang.cpp>
#include <stdio.h>

#include "cpu.h"

namespace cpu {
    Error run(CPU* mainCPU) {
        Error result = Error::OK;

        while (!(result = runCommand(mainCPU)));

        return result == Error::OK_HALT ? Error::OK : result == Error::OK ? Error::UNREACHABLE_HLT : result;
    }

    Error runCommand(CPU* mainCPU) {
        switch (mainCPU->code.code[mainCPU->code.pc]) {
        case asmLang::COMMAND_HALT_CODE:
            printf("HALT\n");
            mainCPU->code.pc += 1;
            return Error::OK_HALT;
        case asmLang::COMMAND_PUSH_CODE:
            printf("PUSH\n");
            mainCPU->code.pc += 2;
            break;
        case asmLang::COMMAND_ADD_CODE:
            printf("ADD\n");
            mainCPU->code.pc += 1;
            break;
        case asmLang::COMMAND_DIV_CODE:
            printf("DIV\n");
            mainCPU->code.pc += 1;
            break;
        case asmLang::COMMAND_OUT_CODE:
            printf("OUT\n");
            mainCPU->code.pc += 1;
            break;
        default:
            return Error::UNKNOWN_COMMAND;
        }

        return Error::OK;
    }
}
