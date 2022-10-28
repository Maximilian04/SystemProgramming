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

const int MAX_CMD_ARGS_COUNT = 64; ///< Size of buffer for flags

namespace cmdParser {
    /**
     * @brief Structure for cmd flags
     *
     */
    typedef struct {
        char key;             ///< flag (like "-h")
        bool isActive;        ///< true if flag is active
        int index;            ///< flags index in "argv"
        bool hasArgument;     ///< true if flag has additional word
        const char* argument; ///< addition word after flag
    } CmdArgument;

    /**
     * @brief  Possible results for cmdParser::processFlags
     *
     * Also BAD_INPUT is used with cmdParser::parse
     */
    enum ParserResult {
        BAD_INPUT = -1,  ///< Input cannot be recognized
        GOOD_INPUT,      ///< Input was recognized
        UNKNOWN_FLAG,    ///< ONLY FOR USER'S handleFlag(): flag wasn't handled (like incorrect or -h)
        FLAG_IS_HANDLED, ///< ONLY FOR USER'S handleFlag(): flag was handled
    };

    /**
     * @brief  Possible results for user's handleFlag()
     */
    enum handleFlagResult {
        INCORRECT_INPUT = -1, ///< Input cannot be recognized
        UNKNOWN,              ///< Flag wasn't handled (like incorrect or -h)
        KNOWN,                ///< Flag was handled
    };

    ParserResult handleFlags(int argc, const char* const* const argv,
        cmdParser::ParserResult(*reactToFlags)(int, cmdParser::CmdArgument*, void*),
        void* userdata);

    cmdParser::ParserResult standartReactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments,
        void* userdata, void printHelpMessage(void),
        cmdParser::handleFlagResult handleFlag(cmdParser::CmdArgument cmdArgument, void* userdata));
}

#endif // CMDPARSER_H
