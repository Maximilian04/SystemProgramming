#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "strAsmLang\strAsmLang.h"

#include "asm.h"

using strAsmLang::getCommandName;
using strAsmLang::classifyArg;
using strAsmLang::classifyReg;

namespace asmbler {
    const int BUFFER_SIZE = 64;

    Error translateLine(Line* asmTextLine, AsmCode* asmCode);
    Error getCommandArg(const Line* line, int* shift, AsmCode_t* argType, AsmCode_t* argValue);
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

    /**
     * @brief Parse current command argument from line
     *
     * @param [in] line Line
     * @param [out] shift Parser's position in line
     * @param [out] argType Type of argument
     * @param [out] argValue Value of argument
     * @return Error Error code
     */
    Error getCommandArg(const Line* line, int* shift, AsmCode_t* argType, AsmCode_t* argValue) {
        assert(line != nullptr);
        assert(shift != nullptr);
        assert(argType != nullptr);
        assert(argValue != nullptr);
        assert(argType != argValue);
        if (*shift > line->lenght)
            return Error::BROKEN_ASMTEXT;

        *argType = classifyArg(line->str[*shift]);
        if (*argType == null)
            return Error::BROKEN_ASMTEXT;

        int scanfRes = 0;
        switch (*argType) {

        case asmLang::COMMAND_ARG_HAS_I:
            // scanfRes = sscanf_s(line->str + *shift, "%" SCNu8, argValue);
            // scanfRes = sscanf_s(line->str + *shift, "%hhu", argValue);
            scanfRes = strAsmLang::sscanAsmCode_t(line->str + *shift, argValue);
            if (scanfRes != 1)
                return Error::COMMAND_SYNTAX;

            switch (strAsmLang::skipSymbols(line, shift, strAsmLang::isCorrectSymbIM)) {
            case strAsmLang::Error::OK:
                break;
            case strAsmLang::Error::BROKEN_LINE:
                return Error::BROKEN_ASMTEXT;
            case strAsmLang::Error::BUF_OVERFLOW:
            default:
                assert(0 && "strAsmLang::skipSymbols()'s result is incorrect in this context");
            }
            break;

        case asmLang::COMMAND_ARG_HAS_R:
            *argValue = classifyReg(line->str[*shift + 1]);
            if (*argValue == null)
                return Error::COMMAND_SYNTAX;
            else
                scanfRes = 1;
            break;

        case asmLang::COMMAND_ARG_HAS_M:
            printf("NO SO FAR");
            break;

        default:
            assert(0 && "classifyArg()'s result is not a correct code");
        }

        return Error::OK;
    }

    Error translateLineArgs(Line* asmTextLine, const int commandNameLength, AsmCode* asmCode) {
        AsmCode_t gotArgs = null;
        AsmCode_t* commandPtr = asmCode::getCodePtr(asmCode);

        for (int strShift = commandNameLength; true;) {
            if (asmTextLine->str[strShift] == '@' ||
                asmTextLine->str[strShift] == '+') {
                strShift++;
            } else {
                break;
            }

            AsmCode_t argCode = null;
            AsmCode_t arg = 0;
            Error getArgRes = getCommandArg(asmTextLine, &strShift, &argCode, &arg);

            if (getArgRes)
                return getArgRes;

            if ((gotArgs & argCode))
                return Error::COMMAND_SYNTAX;
            gotArgs |= argCode;
            *commandPtr |= argCode;
            asmCode::add(asmCode, arg);
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
        } else if (!strcmp(commandName, asmLang::COMMAND_ADD_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_ADD_CODE);
        } else if (!strcmp(commandName, asmLang::COMMAND_DIV_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_DIV_CODE);
        } else if (!strcmp(commandName, asmLang::COMMAND_OUT_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_OUT_CODE);
        } else if (!strcmp(commandName, asmLang::COMMAND_POP_NAME)) {
            asmCode::add(asmCode, asmLang::COMMAND_POP_CODE);
        } else {
            return Error::UNKNOWN_COMMAND;
        }
        argsTranslationRes = translateLineArgs(asmTextLine, commandNameLength, asmCode);

        return argsTranslationRes;
    }
}
