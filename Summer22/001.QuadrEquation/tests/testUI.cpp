#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "testUI.h"

/**
 * @brief Prints help message to console
 *
 */
void printHelpMessage() {
    printf(
        "Help message. Command list:\n"
        "-h\t\tshow help message\n"
        "-f [name]\trun tests from [name] file\n");
}

/**
 * @brief Function with list of reactions to all possible flags
 *
 * @note Must be given to cmdParser::handleFlags
 *
 * @param [in] cmdFlagC Number of active flags
 * @param [in] cmdArguments Array of flags
 * @param [out] userdata Pointer to #ProccessFlagsPtrs casted to (void*)
 * @return cmdParser::ParserResult
 */
cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata) {
    assert(userdata != nullptr);

    if (cmdFlagC == cmdParser::BAD_INPUT) {
        printf("Cannot recognize flags. Please use flags from list below.\n");
        printHelpMessage();
        return cmdParser::ParserResult::BAD_INPUT;
    }

    for (int cmdFlagI = 0; cmdFlagI < cmdFlagC; ++cmdFlagI) {
        assert(cmdArguments[cmdFlagI].isActive);

        switch (cmdArguments[cmdFlagI].key) {
        case 'h':
            printHelpMessage();
            break;
        case 'f':
            if (!cmdArguments[cmdFlagI].hasArgument) {
                printf("Cannot recognize file name after '-f'. Please use flags from list below.\n");
                printHelpMessage();
                return cmdParser::ParserResult::BAD_INPUT;
            }

            *(((ProccessFlagsPtrs*)userdata)->programModePtr) |= ProgramMode::EXT_TEST_FILE;
            *(((ProccessFlagsPtrs*)userdata)->userTestFileNamePtr) = cmdArguments[cmdFlagI].argument;
            break;
        default:
            printf("Unknown flag '-%c'. Please use flags from list below.\n", cmdArguments[cmdFlagI].key);
            printHelpMessage();
            return cmdParser::ParserResult::BAD_INPUT;
            break;
        }
    }
    return cmdParser::ParserResult::GOOD_INPUT;
}
