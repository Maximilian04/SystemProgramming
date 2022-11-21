/**
 * @file graphviz.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Graphviz logging system
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include "ValueOutFunction_t.h"

namespace graphviz {
    enum Error {
        OK = 0,         ///< No errors
        OPEN_FILE_ERR,  ///< Cannot open file
        CLOSE_FILE_ERR, ///< Cannot close file
        GRAPHVIZ_ERR,   ///< Error in graphviz (usually .gv syntax)
    };

    Error openLogFile(const char* fileName);
    Error closeLogFile();

    Error run(size_t bufN, const char* fileGVName, const char* filePNGName);

    void logGraphHead();
    void logGraphTail();

    void logElem(size_t const elemIndex, void const* const elemPtr, void const* const nextPtr, void const* const prevPtr,
        ValueOutFunction_t const outFunc, size_t const bufN, void const* const valuePtr);
    
    void logNode(void const* const elemPtr, void const* const leftPtr, void const* const rightPtr, 
        ValueOutFunction_t const outFunc, size_t const bufN, void const* const valuePtr);

    void logHeadTailEgg(void const* const headPtr, void const* const tailPtr);
}

#endif // GRAPHVIZ_H
