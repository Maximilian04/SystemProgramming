#include <assert.h>

#include <..\asmLang.cpp>
#include <stdio.h>

#include "logger\loggerCPU.h"
#include "cpu.h"

namespace cpu {
#ifdef CPU_DEBUG
    Error ctor(CPU* const cpu, DEBUGINFO_CTOR_ARGS_H, CPU::MODE mode, size_t codeBufferSize) {
#else // !STACK_DEBUG
    Error ctor(CPU* const cpu, CPU::MODE mode, size_t codeBufferSize) {
#endif // STACK_DEBUG
        assert(cpu != nullptr);

        STACK__ctor(cpu->stack));
        cpu->code.codeBufferSize = codeBufferSize == 0 ? asmLang::MAX_CODE_SIZE : codeBufferSize;
        asmCode::createBuf(&cpu->code, cpu->code.codeBufferSize);

        cpu->mode = mode;

#ifdef STACK_DEBUG
        cpu->debugInfo.objName = objName;
        cpu->debugInfo.ctorCallLine = ctorCallLine;
        cpu->debugInfo.ctorCallFile = ctorCallFile;
        cpu->debugInfo.ctorCallFunc = ctorCallFunc;
#endif // STACK_DEBUG

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
        if (mainCPU->mode == CPU::MODE::DISASSEMBLER) {

        }
        switch (mainCPU->code.code[mainCPU->code.pc]) {
        case asmLang::COMMAND_HALT_CODE:
            printf("%s\n", asmLang::COMMAND_HALT_NAME);
            mainCPU->code.pc += 1;
            return Error::OK_HALT;
        case asmLang::COMMAND_PUSH_CODE:
            printf("%s\n", asmLang::COMMAND_PUSH_NAME);
            mainCPU->code.pc += 2;
            break;
        case asmLang::COMMAND_ADD_CODE:
            printf("%s\n", asmLang::COMMAND_ADD_NAME);
            mainCPU->code.pc += 1;
            break;
        case asmLang::COMMAND_DIV_CODE:
            printf("%s\n", asmLang::COMMAND_DIV_NAME);
            mainCPU->code.pc += 1;
            break;
        case asmLang::COMMAND_OUT_CODE:
            printf("%s\n", asmLang::COMMAND_OUT_NAME);
            mainCPU->code.pc += 1;
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
