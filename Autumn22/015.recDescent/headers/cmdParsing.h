/**
 * @file cmdParsing.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief PArsing cmd arguments
 * @date 2022-11-25
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CMDPARSING_H
#define CMDPARSING_H

#include <cmdParser.h>

namespace cmdParser {
    /**
     * @brief Struct for transfering information to cmdParser::processFlags
     *
     */
    typedef struct {
        FILE** testFilePtr;  ///< buffer with user's tests file's name
    } ProccessFlagsPtrs;

    void printHelpMessage();

    cmdParser::handleFlagResult handleFlag(cmdParser::CmdArgument cmdArgument, void* userdata);

    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata);
}

#endif // CMDPARSING_H
