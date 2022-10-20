#include "loggerRegs.h"

#include <..\..\004.Stack\StackLib\StackLibWorld.h>
//#include "logger\logger.h"

namespace logger {
    // void logCPU(const CPU* const cpu) {
    void logRegs(Regs* const regs) {
        logger::addBlock();
#define PR_REGISTER(name, ...) \
        logger__logField(regs, name, AsmCode_t));
#include <..\asmLangDSLRegisters.cpp>
#undef PR_REGISTER
        logger::openLogFile();
        logger::endBlock();
    }
}
