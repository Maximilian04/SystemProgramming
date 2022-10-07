#include <assert.h>
#include <string.h>
#include <stdio.h>

#include <..\asmLang.cpp>
#include "strAsmLang\strAsmLang.h"

#include "asm.h"

using strAsmLang::getCommandName;

namespace asmbler {
    const int BUFFER_SIZE = 64;

    Error translateLine(Line* asmTextLine, AsmCode* asmCode);

    /**
     * @brief Translate asm text to asm code
     *
     * @param [in] asmText Asm text
     * @param [out] asmCode Asm code
     * @return Error Error code
     */
    Error translate(ListOfLines* asmText, AsmCode* asmCode) {
        assert(asmText != nullptr);
        assert(asmCode != nullptr);
        assert(asmText->size != 0);

        for (int lineI = 0; lineI < asmText->size; ++lineI) {
            // printf("%s\n", asmText->lines[lineI].str);

            Error translationRes = translateLine(&asmText->lines[lineI], asmCode);
            switch (translationRes) {
            case Error::BROKEN_ASMTEXT:
            case Error::OVERFLOW_BY_NAME:
            case Error::UNKNOWN_COMMAND:
                return translationRes;
            case Error::OK:
                break;
            default:
                assert(0 && "translateLine's result is not a member of asmbler::Error");
            }
        }
        return Error::OK;
    }

    Error translateLine(Line* asmTextLine, AsmCode* asmCode) {
        assert(asmTextLine != nullptr);

        char commandName[BUFFER_SIZE] = {};
        int commandNameLength = 0;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
        strAsmLang::Error getCommandNameRes = getCommandName(asmTextLine, commandName, &commandNameLength, BUFFER_SIZE);
        switch (getCommandNameRes) {
        case strAsmLang::Error::BUF_OVERFLOW:
            return Error::OVERFLOW_BY_NAME;
        case strAsmLang::Error::BROKEN_LINE:
            return Error::BROKEN_ASMTEXT;
        case strAsmLang::Error::OK:
            break;
        default:
            assert(0 && "getCommandNameRes's result is not a member of strAsmLang::Error");
        }
#pragma GCC diagnostic pop

        if (!strcmp(commandName, asmLang::COMMAND_HALT_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_HALT_CODE);
        } else if (!strcmp(commandName, asmLang::COMMAND_OUT_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_OUT_CODE);
        } else {
            return Error::UNKNOWN_COMMAND;
        }

        return Error::OK;
    }
}

namespace asmCode {
    /**
     * @brief Add command to machine code
     *
     * @param [out] asmCode AsmCode object
     * @param [in] byte Command to add
     */
    void add(AsmCode* asmCode, uint8_t byte) {
        assert(asmCode != nullptr);
        assert(asmCode->code != nullptr);
        // assert(asmCode->pc >= 0);

        asmCode->code[asmCode->pc] = byte;
        asmCode->pc++;
    }
}
