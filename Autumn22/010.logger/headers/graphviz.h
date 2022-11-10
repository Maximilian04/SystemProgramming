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

namespace graphviz {
    enum Error {
        OK = 0,         ///< No errors
        OPEN_FILE_ERR,  ///< Cannot open file
        CLOSE_FILE_ERR, ///< Cannot close file
    };

    Error openLogFile(const char* fileName);
    Error closeLogFile();

    void logGraphHead();
    void logGraphTail();

    void logElem(void const* const elemPtr, void const* const nextPtr, void const* const prevPtr);
}

#endif // GRAPHVIZ_H