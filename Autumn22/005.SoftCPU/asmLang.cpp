/**
 * @file asmLang.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief mAsm language standart
 * @version 0.1
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ASMLANG_CPP
#define ASMLANG_CPP

#include <stdint.h>
// #define __STDC_FORMAT_MACROS 1
// #include <inttypes.h>
// SCNu8

typedef uint8_t AsmCode_t;

namespace asmLang {
    static const size_t MAX_CODE_SIZE = 1024; ///< Size of buffers for machine code

/*    static const char      COMMAND_HALT_NAME[] = "hlt";
    static const AsmCode_t COMMAND_HALT_CODE = 0x00;

    static const char      COMMAND_PUSH_NAME[] = "push";
    static const AsmCode_t COMMAND_PUSH_CODE = 0x01;

    static const char      COMMAND_ADD_NAME[] = "add";
    static const AsmCode_t COMMAND_ADD_CODE = 0x02;

    static const char      COMMAND_DIV_NAME[] = "div";
    static const AsmCode_t COMMAND_DIV_CODE = 0x03;

    static const char      COMMAND_OUT_NAME[] = "out";
    static const AsmCode_t COMMAND_OUT_CODE = 0x04;

    static const char      COMMAND_POP_NAME[] = "pop";
    static const AsmCode_t COMMAND_POP_CODE = 0x05;*/

    static const AsmCode_t COMMAND_ARG_HAS_MASK = 0b11100000;
    static const AsmCode_t COMMAND_ARG_HAS_I    = 0b10000000; ///< Immediate constant
    static const AsmCode_t COMMAND_ARG_HAS_R    = 0b01000000; ///< Register name
    static const AsmCode_t COMMAND_ARG_HAS_M    = 0b00100000; ///< Memory pointer

    static const AsmCode_t RAX_CODE = 0x01;
    static const AsmCode_t RBX_CODE = 0x02;
    static const AsmCode_t RCX_CODE = 0x03;
    static const AsmCode_t RDX_CODE = 0x04;
}

#define null (0)

#endif // ASMLANG_CPP
