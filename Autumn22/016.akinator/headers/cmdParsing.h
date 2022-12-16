/**
 * @file cmdParsing.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Parsing cmd arguments
 * @date 2022-11-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CMDPARSING_H
#define CMDPARSING_H

#include <stdio.h>

#include <cmdParser.h>

#include "include.h"

namespace cmdParser {
    /**
     * @brief Struct for transfering information to cmdParser::processFlags
     *
     */
    typedef struct {
        Mode* modePtr;           ///< program mode
        char const** fileNamePtr; ///< buffer with user's tests file's name
    } ProccessFlagsPtrs;

    void printHelpMessage();

    void openFile(ProccessFlagsPtrs* const proccessFlagsPtrs, char const* const fileName);
    void closeFile(FILE* file);

    cmdParser::handleFlagResult handleFlag(cmdParser::CmdArgument cmdArgument, void* userdata);

    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata);
}

#endif // CMDPARSING_H
