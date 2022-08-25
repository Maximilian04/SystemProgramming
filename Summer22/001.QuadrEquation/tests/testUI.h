/**
 * @file testUI.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Utilitis for testing and working with cmdParser
 * @date 2022-08-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef TESTUI_H
#define TESTUI_H

#include "cmdParser/cmdParser.h"

/**
 * @brief Flags for description of mode program works
 *
 * Can be added via | operator
 */
enum ProgramMode {
    STD_TEST_FILE = 0b0000, ///< Tests from standart file
    EXT_TEST_FILE = 0b0001, ///< Tests from user's file
};

/**
 * @brief Struct for transfering information to cmdParser::processFlags
 * 
 */
typedef struct {
    int* programModePtr;     ///< pointer to actual porgram mode
    const char** userTestFileNamePtr; ///< buffer with user's tests file's name
} ProccessFlagsPtrs;

void printHelpMessage();
cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata);

#endif // TESTUI_H
