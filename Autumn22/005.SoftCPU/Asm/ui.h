/**
 * @file ui.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief User inteface and stuff
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef UI_H
#define UI_H

#include <cmdParser\cmdParser.h>
#include <ListOfLines\ListOfLines.h>

#include "asm.h"

namespace ui {
    /**
     * @brief Codes for errors in returned values
     * 
     */
    enum Error {
        OK = 0,   ///< No errors
        FLAG_ERR, ///< Error in console flags
        FILE_ERR, ///< Error with file
        MEM_ERR,  ///< Some error with memory allocation
    };
    Error handleFlags(const int argc, const char* const* const argv, ListOfLines* asmTextPtr);
    Error translateAsm(ListOfLines* asmText, AsmCode* asmCode);
}

#endif // UI_H