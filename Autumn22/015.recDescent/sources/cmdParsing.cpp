#include <assert.h>
#include <stdio.h>

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
            "-i [name]\tassamble code from [name] file\n"
            "-c\t\tallow you to enter code via console (in future, f*u)\n");
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

            // *((ProccessFlagsPtrs*)userdata)->testFilePtr = autoTest::openTestFile(true, cmdArgument.argument);
            break;
        case 'i':
            *((ProccessFlagsPtrs*)userdata)->testFilePtr = stdin;
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
