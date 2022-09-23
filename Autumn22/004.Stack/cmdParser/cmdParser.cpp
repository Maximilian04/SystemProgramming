#include <string.h>
#include <assert.h>

#include "cmdParser.h"

namespace cmdParser {
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
     * @brief Handle flags and react to it with your function
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
}
