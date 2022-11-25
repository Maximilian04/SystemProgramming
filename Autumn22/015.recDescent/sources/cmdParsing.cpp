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
            "-i [name]\tassamble code from [name] file\n"
            "-c\t\tallow you to enter code via console (in future, f*u)\n");
    }

    /**
     * @brief Open file
     *
     * @param [out] proccessFlagsPtrs
     * @param [in] fileName
     */
    void openFile(ProccessFlagsPtrs* const proccessFlagsPtrs, char const* const fileName) {
        assert(fileName != nullptr);

        FILE* file = fopen(fileName, "rt");

        if (file != NULL) {
            *proccessFlagsPtrs->testFilePtr = file;
            return;
        }
        printf("Cannot open file\n");
    }

    /**
     * @brief Close file
     * 
     * @param [out] file 
     */
    void closeFile(FILE* file) {
        fclose(file);
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

            openFile((ProccessFlagsPtrs*)userdata, cmdArgument.argument);
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

        if (*((ProccessFlagsPtrs*)userdata)->testFilePtr)
            return cmdParser::ParserResult::GOOD_INPUT;
        else
            return cmdParser::ParserResult::BAD_INPUT;
    }
}
