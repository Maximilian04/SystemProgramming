#include <string.h>

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
}
