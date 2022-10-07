/**
 * @file fileIO.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Functions for setting output file
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef FILEIO_H
#define FILEIO_H

#include "asm.h"

namespace fileIO {
    const size_t MAX_FILENAME_SIZE = 64; ///< Size of buffer for filename

    /**
     * @brief Codes for errors in returned values
     *
     */
    enum Error {
        OK = 0, ///< No errors

    };

    Error writeAsmCode2File(AsmCode* asmCode, const char* const proposedFileName);
};

#endif // FILEIO_H
