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
#include <..\AsmCode.h>

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
    Error skipSymbols(const Line* line, int* shift, bool isCorrect(char symb));
    bool isCorrectSymbIM(char symb);
    bool isCorrectSymbR(char symb);
    AsmCode_t classifyArg(char symb);
    AsmCode_t classifyReg(char key);

    int sscanAsmCode_t(char const* str, AsmCode_t* const a);
}

#endif // ATRASMLANG_H
