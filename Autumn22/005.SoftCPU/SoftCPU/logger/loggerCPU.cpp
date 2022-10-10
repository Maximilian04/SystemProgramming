#include "loggerCPU.h"

#include <..\..\004.Stack\StackLib\StackLibWorld.h>
//#include "logger\logger.h"

namespace logger {
    void logCPUCode(const CPU* const cpu);
    // void logCPUStack(const CPU* const cpu);
    void logCPUStack(CPU* const cpu);

    void logCPUCode(const CPU* const cpu) {
        if (cpu != nullptr) {
            logger::logMsg(COLORED_TEXT("Teal", "Here will be AsmCode dump"));
            logger::openLogFile();
        }
    }

    // void logCPUStack(const CPU* const cpu) {
    void logCPUStack(CPU* const cpu) {
        STACK__dump(cpu->stack));
    }

    // void logCPU(const CPU* const cpu) {
    void logCPU(CPU* const cpu) {
        logger::addBlock();
        logCPUCode(cpu);
        logCPUStack(cpu);
        logger::openLogFile();
        logger::endBlock();
    }
}
