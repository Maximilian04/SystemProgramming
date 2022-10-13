#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "strAsmLang\strAsmLang.h"

#include "asm.h"

using strAsmLang::getCommandName;
using strAsmLang::classifyArg;

namespace asmbler {
    const int BUFFER_SIZE = 64;

    Error translateLine(Line* asmTextLine, AsmCode* asmCode);
    Error translateLineArgs(Line* asmTextLine, const int commandNameLength, AsmCode* asmCode);

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

        if (asmCode->code == nullptr) {
            asmCode::createBuf(asmCode);
        }
        asmCode->pc = 0;

        for (int lineI = 0; lineI < asmText->size; ++lineI) {
            // printf("%s\n", asmText->lines[lineI].str);

            Error translationRes = translateLine(&asmText->lines[lineI], asmCode);
            switch (translationRes) {
            case Error::BROKEN_ASMTEXT:
            case Error::OVERFLOW_BY_NAME:
            case Error::UNKNOWN_COMMAND:
            case Error::COMMAND_SYNTAX:
                return translationRes;
            case Error::OK:
                break;
            default:
                assert(0 && "translateLine's result is not a member of asmbler::Error");
            }
        }
        return Error::OK;
    }

    Error translateLineArgs(Line* asmTextLine, const int commandNameLength, AsmCode* asmCode) {
        AsmCode_t gotArgs = null;

        for (int strShift = commandNameLength; asmTextLine->str[strShift++] == '@';) {
            AsmCode_t argCode = classifyArg(asmTextLine->str[strShift]);
            AsmCode_t arg = 0;
            int argScanRes = 0;

            if ((gotArgs & argCode))
                return Error::COMMAND_SYNTAX;
            gotArgs |= argCode;
            *asmCode |= argCode;
            switch (argCode) {
            case asmLang::COMMAND_ARG_HAS_I:
                argScanRes = sscanf_s(asmTextLine->str + strShift, "%u", &arg);
                break;
            case asmLang::COMMAND_ARG_HAS_R:
                printf("NO SO FAR");
                break;
            case asmLang::COMMAND_ARG_HAS_M:
                printf("NO SO FAR");
                break;
            default:
                assert(0 && "classifyArg()'s result is not a correct code");
            }

            if (argScanRes != 1)
                return Error::COMMAND_SYNTAX;
            asmCode::add(asmCode, arg);
            break;
        }

        return Error::OK;
    }

    Error translateLine(Line* asmTextLine, AsmCode* asmCode) {
        assert(asmTextLine != nullptr);
        assert(asmCode != nullptr);

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

        Error argsTranslationRes = Error::OK;
        if (!strcmp(commandName, asmLang::COMMAND_HALT_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_HALT_CODE);
        } else if (!strcmp(commandName, asmLang::COMMAND_PUSH_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_PUSH_CODE);
            argsTranslationRes = translateLineArgs(asmTextLine, commandNameLength, asmCode);
        } else if (!strcmp(commandName, asmLang::COMMAND_ADD_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_ADD_CODE);
        } else if (!strcmp(commandName, asmLang::COMMAND_DIV_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_DIV_CODE);
        } else if (!strcmp(commandName, asmLang::COMMAND_OUT_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_OUT_CODE);
        } else {
            return Error::UNKNOWN_COMMAND;
        }

        return argsTranslationRes;
    }
}
