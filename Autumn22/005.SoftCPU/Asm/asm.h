/**
 * @file asm.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Assembler
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ASM_H
#define ASM_H

#include <ListOfLines\ListOfLines.h>
#include <..\AsmCode.h>
#include "FixupsTable.h"

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
        COMMAND_SYNTAX,   ///< Syntax error: invalid command syntax
    };

    Error translate(ListOfLines* asmText, AsmCode* asmCode, FixupsTable* fixupsTable);
}

#endif // ASM_H
