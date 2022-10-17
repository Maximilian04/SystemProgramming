#include "loggerMem.h"

#include <..\..\004.Stack\StackLib\StackLibWorld.h>
//#include "logger\logger.h"

namespace logger {
    // void logCPU(const CPU* const cpu) {
    void logMem(Mem* const mem) {
        logger::addBlock();
        // logger__logField(regs, a, AsmCode_t));
        logger__logField(mem, size, size_t));
        logger__logFieldArray(mem, RAM, mem->size, AsmCode_t));
        logger::openLogFile();
        logger::endBlock();
    }
}
