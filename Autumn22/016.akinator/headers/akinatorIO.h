/**
 * @file akinatorIO.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Stuff for saving and uploading akinator
 * @date 2022-12-02
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef AKINATORIO_H
#define AKINATORIO_H

#include <Tree.h>

namespace akinatorIO {
    enum Error {
        OK = 0,          ///< No errors
        FILE_ERR,        ///< Error with file writing or reading
        FILE_FORMAT_ERR, ///< Error with file format
        ISNOT_EMPTY,     ///< Object to write is not empty
        MEM_ERR,         ///< Error with memory allocation
    };

    Error save(Tree const* const data, char const* const fileName);
    Error upload(Tree* const data, char const* const fileName);
}

#endif // AKINATORIO_H
