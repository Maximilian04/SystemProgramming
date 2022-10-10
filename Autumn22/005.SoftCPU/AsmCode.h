/**
 * @file AsmCode.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Machine code for Assembler & SoftCPU
 * @date 2022-10-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ASMCODE_H
#define ASMCODE_H

#include "asmLang.cpp"
#include <stdint.h>

typedef uint8_t AsmCode_t;

/**
 * @brief Struct for translated asm code
 *
 */
struct AsmCode {
    AsmCode_t* code; ///< Bytes sequence
    size_t pc;     ///< Current program counter
};

namespace asmCode {
    int createBuf(AsmCode* asmCode);
    int createBuf(AsmCode* asmCode, size_t size);
    int freeBuf(AsmCode* asmCode);

    void add(AsmCode* asmCode, AsmCode_t byte);
}

#endif // ASMCODE_H