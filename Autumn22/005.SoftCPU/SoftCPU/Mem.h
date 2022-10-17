/**
 * @file Mem.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Rgister object
 * @date 2022-10-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef MEM_H
#define MEM_H

#include <..\..\004.Stack\StackLib\StackLibWorld.h>
#include <..\AsmCode.h>

#ifndef NDEBUG
#ifdef MEM_DEBUG
#else // !STACK_DEBUG
#define MEM_DEBUG
#endif // STACK_DEBUG
#endif // NDEBUG

struct Mem {
    AsmCode_t* RAM;
    size_t size;

#ifdef MEM_DEBUG
    DebugInfo debugInfo;
#endif // MEM_DEBUG
};

namespace mem {
    AsmCode_t* getRAM(Mem* mem, size_t addr);

    const AsmCode_t POISONAsmCode_t = 0xD;
    stack_POISONDEF_PTR(AsmCode_t);
    stack_POISONDEF(size_t);
    
    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0, ///< No errors
        CALLOC, ///< Error in memory allocation
    };

#ifdef MEM_DEBUG
#define MEM__ctor(obj) mem::ctor(&obj, DEBUGINFO_CTOR_ARGS_R(#obj)
    Error ctor(Mem* const mem, DEBUGINFO_CTOR_ARGS_H, size_t size);
#else // !MEM_DEBUG
#define MEM__ctor(obj) mem::ctor(&obj
    Error ctor(Mem* const mem, size_t size);
#endif // MEM_DEBUG

    Error dtor(Mem* const mem);

#define MEM__dump(stackObj) mem::dump(&stackObj, LOGFUNCHEAD_ARGS_R
    Error dump(Mem* const mem, LOGFUNCHEAD_ARGS_H);
}

#endif // MEM_H
