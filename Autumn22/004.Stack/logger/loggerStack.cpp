#include "loggerStack.h"

#include "..\logger\logger.h"

namespace logger {
    void logStack(const Stack* stack) {
        logger::beginBlock();
        LOGGER_logField(stack, size);
        LOGGER_logField(stack, capacity);
        LOGGER_logFieldArray(stack, data, stack->capacity);
        logger::beginBlock();
        logger::logLine("[0] =");
        logger::logStrS("*", -1);
        logger::logStrS("1", 6);
        logger::logLine("[1] =");
        logger::logStrS("*", -1);
        logger::logStrS("2", 6);
        logger::logLine("[2] =");
        logger::logStrS("*", -1);
        logger::logStrS("3", 6);
        logger::logLine("[3] =");
        logger::logStrS("NAN (POISON)", 6);
        logger::logLine("[4] =");
        logger::logStrS("NAN (POISON)", 6);
        logger::endBlock();
        logger::endBlock();
    }
}
