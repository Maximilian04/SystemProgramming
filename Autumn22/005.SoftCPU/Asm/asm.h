/**
 * @file asm.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Asm code
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ASM_H
#define ASM_H

#include <stdint.h>
#include <ListOfLines\ListOfLines.h>

/**
 * @brief Struct for translated asm code
 *
 */
struct AsmCode {
    uint8_t* code; ///< Bytes sequence
    size_t pc;     ///< Current program counter
};

namespace asmCode {
    void add(AsmCode* asmCode, uint8_t byte);
}

namespace asmbler {
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0,           ///< No errors
        BROKEN_ASMTEXT,   ///< Error inside of ListOfLines struc
        OVERFLOW_BY_NAME, ///< Name overflowed buffer
        UNKNOWN_COMMAND,  ///< Syntax error: unknown command
    };

    Error translate(ListOfLines* asmText, AsmCode* asmCode);
}

#endif // ASM_H
