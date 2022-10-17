#include "loggerCPU.h"

#include <..\..\004.Stack\StackLib\StackLibWorld.h>
//#include "logger\logger.h"

namespace logger {
    // void logCPU(const CPU* const cpu) {
    void logRegs(Regs* const regs) {
        logger::addBlock();
        logger__logField(regs, a, AsmCode_t));
        logger__logField(regs, b, AsmCode_t));
        logger__logField(regs, c, AsmCode_t));
        logger__logField(regs, d, AsmCode_t));
        logger::openLogFile();
        logger::endBlock();
    }
}
