/**
 * @file ui.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief User inteface and stuff
 * @date 2022-10-06
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef UI_H
#define UI_H

#include <cmdParser\cmdParser.h>

namespace ui {
    /**
     * @brief Struct for transfering information to cmdParser::processFlags
     *
     */
    typedef struct {
        FILE** testFilePtr;  ///< buffer with user's tests file's name
    } ProccessFlagsPtrs;

    /**
     * @brief Codes for errors in returned values
     * 
     */
    enum Error {
        OK = 0,   ///< No errors
        FLAG_ERR, ///< Error in console flags
        FILE_ERR, ///< Error with file
    };
    Error handleFlags(const int argc, const char* const* const argv);
    Error closeInputFile();
}

#endif // UI_H
