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

namespace asmLang {
    static const size_t MAX_CODE_SIZE = 1024; ///< Size of buffers for machine code

    static const char    COMMAND_HALT_NAME[] = "hlt";
    static const uint8_t COMMAND_HALT_CODE = 0x00;

    static const char    COMMAND_OUT_NAME[] = "out";
    static const uint8_t COMMAND_OUT_CODE = 0x03;
}

#endif // ASMLANG_CPP
