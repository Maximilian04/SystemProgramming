/**
 * @file loggerCPU.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Logging system for CPU class
 * @date 2022-10-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LOGGERCPU_H
#define LOGGERCPU_H

#include "Regs.h"

namespace logger {
    void logRegs(Regs* const regs);
}

#endif // LOGGERSTACK_H
