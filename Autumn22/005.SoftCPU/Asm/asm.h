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
    size_t size;   ///< Size of code sequence
};


namespace asmbler {
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0,
    };

    Error translate(ListOfLines* asmText, AsmCode* asmCode);
}

#endif // ASM_H
