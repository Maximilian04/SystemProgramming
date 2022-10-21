/**
 * @file Regs.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Rgister object
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef REGS_H
#define REGS_H

#include <..\..\004.Stack\StackLib\StackLibWorld.h>
#include <..\AsmCode.h>

#ifndef NDEBUG
#ifdef REGS_DEBUG
#else // !STACK_DEBUG
#define REGS_DEBUG
#endif // STACK_DEBUG
#endif // NDEBUG

struct Regs {
#define PR_REGISTER(name, ...) \
    AsmCode_t name;
#include <..\asmLangDSLRegisters.cpp>
#undef PR_REGISTER

#ifdef REGS_DEBUG
    DebugInfo debugInfo;
#endif // REGS_DEBUG
};

namespace regs {
    AsmCode_t* getReg(Regs* regs, AsmCode_t code);
    // char getRegName(Regs* regs, AsmCode_t* ptr);

    const AsmCode_t POISONAsmCode_t = 0xD;
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0,          ///< No errors
    };

#ifdef REGS_DEBUG
#define REGS__ctor(obj) regs::ctor(&obj, DEBUGINFO_CTOR_ARGS_R(#obj)
    Error ctor(Regs* const regs, DEBUGINFO_CTOR_ARGS_H);
#else // !REGS_DEBUG
#define REGS__ctor(obj) regs::ctor(&obj
    Error ctor(Regs* const regs);
#endif // REGS_DEBUG

    Error dtor(Regs* const regs);

#define REGS__dump(stackObj) regs::dump(&stackObj, LOGFUNCHEAD_ARGS_R
    Error dump(Regs* const regs, LOGFUNCHEAD_ARGS_H);
}

#endif // REGS_H
