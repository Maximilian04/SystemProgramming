#include <assert.h>

#include <..\asmLang.cpp>
#include <stdio.h>

#include "logger\loggerCPU.h"
#include "cpu.h"

struct CommandArgs {
    AsmCode_t command;

    AsmCode_t argI;
    AsmCode_t argR;
    AsmCode_t argM;

    AsmCode_t* argRPtr;

    AsmCode_t argSum;
};

namespace cpu {
    Error parseCommandArgs(CPU* cpu, CommandArgs* args);

    Error parseCommandArgs(CPU* cpu, CommandArgs* args) {
        args->command = cpu->code.code[cpu->code.pc];
        cpu->code.pc += 1;

        if (args->command & asmLang::COMMAND_ARG_HAS_I) {
            args->argI = cpu->code.code[cpu->code.pc];
            cpu->code.pc += 1;
        }
        if (args->command & asmLang::COMMAND_ARG_HAS_R) {
            args->argRPtr = regs::getReg(&cpu->regs, cpu->code.code[cpu->code.pc]);
            if (args->argRPtr == nullptr) return Error::UNKNOWN_REGISTER;
            args->argR = *args->argRPtr;
            cpu->code.pc += 1;
        }
        if (args->command & asmLang::COMMAND_ARG_HAS_M) {
            args->argM = cpu->code.code[cpu->code.pc];
            cpu->code.pc += 1;
        }

        args->argSum = args->argI + args->argR + args->argM;
        args->command &= (~asmLang::COMMAND_ARG_HAS_MASK);
        return Error::OK;
    }


#ifdef CPU_DEBUG
    Error ctor(CPU* const cpu, DEBUGINFO_CTOR_ARGS_H, CPU::MODE mode, size_t codeBufferSize) {
#else // !CPU_DEBUG
    Error ctor(CPU* const cpu, CPU::MODE mode, size_t codeBufferSize) {
#endif // CPU_DEBUG
        assert(cpu != nullptr);

        STACK__ctor(cpu->stack));
        cpu->code.codeBufferSize = codeBufferSize == 0 ? asmLang::MAX_CODE_SIZE : codeBufferSize;
        asmCode::createBuf(&cpu->code, cpu->code.codeBufferSize);

        REGS__ctor(cpu->regs));

        cpu->mode = mode;

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

    Error run(CPU* mainCPU) {
        Error result = Error::OK;

        while (!(result = runCommand(mainCPU)));

        return result == Error::OK_HALT ? Error::OK : result == Error::OK ? Error::UNREACHABLE_HLT : result;
    }

    Error runCommand(CPU* mainCPU) {
        assert(mainCPU != nullptr);

        CommandArgs commandArgs = {};
        Error argsErr = parseCommandArgs(mainCPU, &commandArgs);
        if (argsErr) return argsErr;

        if (mainCPU->mode == CPU::MODE::DISASSEMBLER) {
            switch (commandArgs.command) {
            case asmLang::COMMAND_HALT_CODE:
                printf("%s\n", asmLang::COMMAND_HALT_NAME);
                return Error::OK_HALT;
            case asmLang::COMMAND_PUSH_CODE:
                printf("%s\n", asmLang::COMMAND_PUSH_NAME);
                break;
            case asmLang::COMMAND_ADD_CODE:
                printf("%s\n", asmLang::COMMAND_ADD_NAME);
                break;
            case asmLang::COMMAND_DIV_CODE:
                printf("%s\n", asmLang::COMMAND_DIV_NAME);
                break;
            case asmLang::COMMAND_OUT_CODE:
                printf("%s\n", asmLang::COMMAND_OUT_NAME);
                break;
            case asmLang::COMMAND_POP_CODE:
                printf("%s\n", asmLang::COMMAND_POP_NAME);
                break;
            default:
                return Error::UNKNOWN_COMMAND;
            }

            return Error::OK;
        }

        switch (commandArgs.command) {
        case asmLang::COMMAND_HALT_CODE:
            return Error::OK_HALT;
        case asmLang::COMMAND_PUSH_CODE:
            stack::push(&mainCPU->stack, commandArgs.argSum);
            break;
        case asmLang::COMMAND_ADD_CODE: {
            Elem_t a = 0, b = 0;
            stack::pop(&mainCPU->stack, &b);
            stack::pop(&mainCPU->stack, &a);
            stack::push(&mainCPU->stack, a + b);
            }
            break;
        case asmLang::COMMAND_DIV_CODE: {
            Elem_t a = 0, b = 0;
            stack::pop(&mainCPU->stack, &b);
            stack::pop(&mainCPU->stack, &a);
            stack::push(&mainCPU->stack, a / b);
            }
            break;
        case asmLang::COMMAND_OUT_CODE: {
            Elem_t a = 0;
            stack::pop(&mainCPU->stack, &a);
            printf("%u\n", a);
            }
            break;
        case asmLang::COMMAND_POP_CODE:
            stack::pop(&mainCPU->stack, commandArgs.argRPtr);
            break;
        default:
            return Error::UNKNOWN_COMMAND;
        }

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
