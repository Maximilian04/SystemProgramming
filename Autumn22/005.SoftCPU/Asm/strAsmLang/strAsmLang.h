/**
 * @file strAsmLang.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief String function for Asm Language
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ATRASMLANG_H
#define ATRASMLANG_H

#include <ListOfLines\ListOfLines.h>

namespace strAsmLang {
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0,       ///< No errors
        BUF_OVERFLOW, ///< Buffer overflow
        BROKEN_LINE,  ///< Error inside Line object (ex. wrong length)
    };

    Error getCommandName(const Line* line, char* buffer, int* length, int maxLength);
}

#endif // ATRASMLANG_H
