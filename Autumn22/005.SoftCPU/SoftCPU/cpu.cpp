#include <assert.h>

#include <..\asmLang.cpp>
#include <stdio.h>

#include "logger\loggerCPU.h"
#include "cpu.h"

struct CommandArgs {
    AsmCode_t command;
    AsmCode_t rawCommand;

    AsmCode_t argI;
    AsmCode_t argR;

    AsmCode_t* argWritePtr;

    AsmCode_t argSum;
};

namespace cpu {
    Error parseCommandArgs(CPU* cpu, CommandArgs* args);
    void printArgs(CommandArgs* args);

    Error parseCommandArgs(CPU* cpu, CommandArgs* args) {
        args->command = cpu->code.code[cpu->code.pc];
        cpu->code.pc += 1;

        if (args->command & asmLang::COMMAND_ARG_HAS_I) {
            args->argI = cpu->code.code[cpu->code.pc];
            cpu->code.pc += 1;
        }
        if (args->command & asmLang::COMMAND_ARG_HAS_R) {
            args->argWritePtr = regs::getReg(&cpu->regs, cpu->code.code[cpu->code.pc]);
            if (args->argWritePtr == nullptr) return Error::UNKNOWN_REGISTER;
            args->argR = *args->argWritePtr;
            cpu->code.pc += 1;
        }

        args->argSum = (AsmCode_t)(args->argI + args->argR);

        if (args->command & asmLang::COMMAND_ARG_HAS_M) {
            args->argWritePtr = mem::getRAM(&cpu->mem, args->argSum);
            args->argSum = *(args->argWritePtr);
            // printf("memory access: %u\n", args->argSum);
            if (args->argWritePtr == nullptr) return Error::UNKNOWN_MEMORY;
        }

#pragma GCC diagnostic ignored "-Wconversion" // Warning about (~AsmCode_t) -> int -> AsmCode_t conversion
#pragma GCC diagnostic push
        args->rawCommand = args->command;
        args->command &= (~asmLang::COMMAND_ARG_HAS_MASK);
#pragma GCC diagnostic pop
        return Error::OK;
    }

    void printArgs(CommandArgs* args) {
        if (args->rawCommand & asmLang::COMMAND_ARG_HAS_M) {
            printf("[");
        }
        if (args->rawCommand & asmLang::COMMAND_ARG_HAS_R) {
            char letter = 'a' + args->argR;
            printf("r%cx", letter);
        }
        if (args->rawCommand & asmLang::COMMAND_ARG_HAS_I) {
            printf("+%u", args->argI);
        }
        if (args->rawCommand & asmLang::COMMAND_ARG_HAS_M) {
            printf("]");
        }
    }


#ifdef CPU_DEBUG
    Error ctor(CPU* const cpu, DEBUGINFO_CTOR_ARGS_H, size_t RAMsize, CPU::MODE mode, size_t codeBufferSize) {
#else // !CPU_DEBUG
    Error ctor(CPU* const cpu, size_t RAMsize, CPU::MODE mode, size_t codeBufferSize) {
#endif // CPU_DEBUG
        assert(cpu != nullptr);

        if (STACK__ctor(cpu->stack))) return Error::CTOR_ERR;
        if (STACK__ctor(cpu->funcStack))) return Error::CTOR_ERR;

        cpu->code.codeBufferSize = codeBufferSize == 0 ? asmLang::MAX_CODE_SIZE : codeBufferSize;
        asmCode::createBuf(&cpu->code, cpu->code.codeBufferSize);

        if (REGS__ctor(cpu->regs))) return Error::CTOR_ERR;

        cpu->mode = mode;

        if (MEM__ctor(cpu->mem), RAMsize)) return Error::CTOR_ERR;

#ifdef CPU_DEBUG
        cpu->debugInfo.objName = objName;
        cpu->debugInfo.ctorCallLine = ctorCallLine;
        cpu->debugInfo.ctorCallFile = ctorCallFile;
        cpu->debugInfo.ctorCallFunc = ctorCallFunc;
#endif // CPU_DEBUG

        return Error::OK;
    }

    Error dtor(CPU* const cpu) {
        assert(cpu != nullptr);
        asmCode::freeBuf(&cpu->code);
        return Error::OK;
    }

    Error run(CPU * mainCPU) {
        Error result = Error::OK;

        while (!(result = runCommand(mainCPU)));

        return result == Error::OK_HALT ? Error::OK : result == Error::OK ? Error::UNREACHABLE_HLT : result;
    }

    Error runCommand(CPU * mainCPU) {
        assert(mainCPU != nullptr);

        CommandArgs commandArgs = {};
        Error argsErr = parseCommandArgs(mainCPU, &commandArgs);
        if (argsErr) return argsErr;

        if (mainCPU->mode == CPU::MODE::DISASSEMBLER) {
            if (mainCPU->code.pc >= mainCPU->code.codeBufferSize)
                return Error::OK_HALT;

            switch (commandArgs.command) {
#define DESCRIPT_COMMAND(name, code, ...) \
            case code:                     \
                printf("%s ", name);        \
                printArgs(&commandArgs);     \
                printf("\n");                 \
                break;
#include <..\asmLangDSLInstructions.cpp>
            default:
                return Error::UNKNOWN_COMMAND;
            }
#undef DESCRIPT_COMMAND

            return Error::OK;
        }

        switch (commandArgs.command) {
#define DESCRIPT_COMMAND(name, code, runInstruction, ...) \
        case code:                                         \
            runInstruction                                  \
            break;
#define  POP(ptr)             stack::pop( &mainCPU->stack,       ptr)
#define PUSH(value)           stack::push(&mainCPU->stack,     value)
#define  POP_FUNCSTACK(ptr)   stack::pop( &mainCPU->funcStack,   ptr)
#define PUSH_FUNCSTACK(value) stack::push(&mainCPU->funcStack, value)
#define VAR(name) AsmCode_t name = 0
#define GET_VAR(name) \
    VAR(name);         \
    POP(&name);
#define SET_PC(value) mainCPU->code.pc = value
#define CHANGE_PC SET_PC(commandArgs.argSum)
#define TO_ASM_TYPE(value) (AsmCode_t)value
#define HAULT return Error::OK_HALT;
#include <..\asmLangDSLInstructions.cpp>
        default:
            return Error::UNKNOWN_COMMAND;
        }
#undef  POP
#undef PUSH
#undef  POP_FUNCSTACK
#undef PUSH_FUNCSTACK
#undef VAR
#undef GET_VAR
#undef SET_PC
#undef CHANGE_PC
#undef TO_ASM_TYPE
#undef HAULT
#undef DESCRIPT_COMMAND

        return Error::OK;
    }

    Error dump(CPU* const cpu, LOGFUNCHEAD_ARGS_H) {
        assert(cpu != nullptr); //TODO Dump (nullptr)
        assert(funcName != nullptr);
        assert(fileName != nullptr);
        logger::openLogFile();

        logger::logHtmlHead();
        logger__logFuncHead());
        if (cpu == nullptr) {
            logger::emergencyLog("CPU is nullptr");
            assert(false);
        } else {
#ifdef CPU_DEBUG
            logger::logStructHeadDebug("CPU", cpu, &cpu->debugInfo);
#else // !CPU_DEBUG
            logger::logStructHead("CPU", cpu);
#endif // CPU_DEBUG
            logger::logCPU(cpu);
        }
        logger::logHtmlTail();

        logger::closeLogFile();

        return Error::OK;
    }
}
