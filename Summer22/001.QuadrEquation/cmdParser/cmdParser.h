/**
 * @file cmdParser.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Utilitys for parse cmd arguments
 * @date 2022-08-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CMDPARSER_H
#define CMDPARSER_H

const int MAX_CMD_ARG_LENGTH = 64; ///< Size of string buffer for one cmd argument
const int MAX_CMD_ARGS_COUNT = 64; ///< Size of buffer for flags

namespace cmdParser {
    /**
     * @brief Structure for cmd flags
     *
     */
    typedef struct {
        char key;                          ///< flag (like "-h")
        bool isActive;                     ///< true if flag is active
        int index;                         ///< flags index in "argv"
        bool hasArgument;                  ///< true if flag has additional word
        char argument[MAX_CMD_ARG_LENGTH]; ///< addition word after flag
        // TODO можно записывать указатель на argv
    } CmdArgument;

    /**
     * @brief  Possible results for cmdParser::processFlags
     *
     * Alse BAD_INPUT is used with cmdParser::parse
     */
    enum ParserResult {
        BAD_INPUT = -1,                   ///< Input cannot be recognized
        GOOD_INPUT,                       ///< Input was recognized
    };

    int parse(int argc, char** argv, CmdArgument* flags);

    /**
     * @brief Function with description of reactions to flags
     *
     * @param [in] argc Cmd arguments
     * @param [in] argv Cmd arguments
     * @param [in] userdata void* for various information
     * @return ParserResult Result of processing
     * @warning Must be declared in file using it!
     */
    ParserResult processFlags(int argc, char** argv, void* userdata = nullptr);
}

#endif // CMDPARSER_H
