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
    void dodo();
}

#endif // CPU_H
