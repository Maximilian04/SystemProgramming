#include <assert.h>

#include "cmdParsing.h"

namespace cmdParser {
    /**
     * @brief Prints help message to console
     *
     */
    void printHelpMessage() {
        printf(
            "Help message. Command list:\n"
            "-h\t\tshow help message\n"
            "-f [name]\tuse database from [name] file\n"
            "-d\t\tdefenition mode\n"
            "-~\t\tcomparing mode\n");
    }

    cmdParser::handleFlagResult handleFlag(cmdParser::CmdArgument cmdArgument, void* userdata) {
        assert(userdata != nullptr);

        switch (cmdArgument.key) {
        case 'f':
            if (!cmdArgument.hasArgument) {
                printf("Cannot recognize file name after '-f'. Please use flags from list below.\n");
                printHelpMessage();
                return cmdParser::handleFlagResult::INCORRECT_INPUT;
            }

            *((ProccessFlagsPtrs*)userdata)->fileNamePtr = cmdArgument.argument;
            break;
        case 'd':
            *((ProccessFlagsPtrs*)userdata)->modePtr = Mode::DEFENITION;
            break;
        case '~':
            *((ProccessFlagsPtrs*)userdata)->modePtr = Mode::DIFFERENCE;
            break;
        default:
            return cmdParser::handleFlagResult::UNKNOWN;
        }

        return cmdParser::handleFlagResult::KNOWN;
    }

    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata) {
        cmdParser::ParserResult res = cmdParser::standartReactToFlags(cmdFlagC, cmdArguments, userdata, printHelpMessage, handleFlag);
        if (res) return res;

        return cmdParser::ParserResult::GOOD_INPUT;
    }
}
