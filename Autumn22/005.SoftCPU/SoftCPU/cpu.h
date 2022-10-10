/**
 * @file cpu.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Soft CPU code
 * @date 2022-10-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CPU_H
#define CPU_H

#include <..\AsmCode.h>

struct CPU {
    AsmCode code;
};


namespace cpu {
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0,          ///< No errors, program had to continue
        OK_HALT,         ///< No errors, program had to stop
        UNREACHABLE_HLT, ///< Unreacheble point in program is reached. !!! Sth. has gone VARY wrong
        UNKNOWN_COMMAND, ///< Code error: unknown command
    };
    Error run(CPU* mainCPU);
    Error runCommand(CPU* mainCPU);
}

#endif // CPU_H
