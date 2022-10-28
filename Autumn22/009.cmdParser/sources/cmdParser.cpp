#include <stdio.h>
#include <assert.h>

#include "cmdParser.h"

namespace cmdParser {
    int parse(int argc, const char* const* const argv, CmdArgument* flags);

    /**
     * @brief Recognizes flags in cmd input
     *
     * Write recognized flags to "flags"
     *
     * @param [in] argc Cmd arguments
     * @param [in] argv Cmd arguments
     * @param [out] flags array with recognized information
     * @return int Number of keys or cmdParser::PARSER_RESULT::BAD_INPUT
     * @warning Returns BAD_INPUT if cannot recognize all flags
     */
    int parse(int argc, const char* const* const argv, CmdArgument* flags) {
        assert(argv != nullptr);
        assert(flags != nullptr);

        int flagsNumber = 0;
        for (int argI = 1; argI < argc; ++argI) {
            if (argv[argI][0] == '-') {
                flags[flagsNumber].isActive = true;
                flags[flagsNumber].index = argI;
                flags[flagsNumber].key = argv[argI][1];

                flagsNumber++;
            } else {
                if (flagsNumber > 0 && flags[flagsNumber - 1].index == (argI - 1)) {
                    flags[flagsNumber - 1].hasArgument = true;
                    flags[flagsNumber - 1].argument = argv[argI];
                } else {
                    return ParserResult::BAD_INPUT;
                }
            }
        }

        return flagsNumber;
    }

    /**
     * @brief Handle flags and react to its with your function
     *
     * @param [in] argc Cmd arguments
     * @param [in] argv Cmd arguments
     * @param reactToFlags Function with description of reactions to flags
     * @param [in] userdata void* for various information
     * @return ParserResult Result of handling
     */
    ParserResult handleFlags(int argc, const char* const* const argv,
        cmdParser::ParserResult(*reactToFlags)(int, cmdParser::CmdArgument*, void*),
        void* userdata = nullptr) {
        assert(argv != nullptr);
        assert(reactToFlags != nullptr);

        cmdParser::CmdArgument cmdArguments[MAX_CMD_ARGS_COUNT] = {};
        int cmdFlagC = cmdParser::parse(argc, argv, cmdArguments);

        return reactToFlags(cmdFlagC, cmdArguments, userdata);
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

    cmdParser::ParserResult standartReactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments,
        void* userdata, void printHelpMessage(void),
        cmdParser::handleFlagResult handleFlag(cmdParser::CmdArgument cmdArgument, void* userdata)) {

        assert(cmdArguments != nullptr);
        assert(printHelpMessage != nullptr);
        assert(handleFlag != nullptr);

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
            default:
                switch (handleFlag(cmdArguments[cmdFlagI], userdata)) {
                case handleFlagResult::INCORRECT_INPUT:
                    return ParserResult::BAD_INPUT;
                case handleFlagResult::UNKNOWN:
                    break;
                case handleFlagResult::KNOWN:
                    return ParserResult::GOOD_INPUT;
                default:
                    assert(0 && "handleFlag's result is not an allowed member of cmdParser::ParserResult");
                }

                printf("Unknown flag '-%c'. Please use flags from list below.\n", cmdArguments[cmdFlagI].key);
                printHelpMessage();
                return cmdParser::ParserResult::BAD_INPUT;
                break;
            }
        }

        return cmdParser::ParserResult::GOOD_INPUT;
    }
}
