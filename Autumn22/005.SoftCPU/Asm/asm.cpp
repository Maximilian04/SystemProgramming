#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "strAsmLang\strAsmLang.h"

#include "asm.h"

using strAsmLang::getCommandName;
using strAsmLang::isNameLabel;
using strAsmLang::classifyArg;
using strAsmLang::classifyReg;

namespace asmbler {
    Error translateLine(Line* asmTextLine, AsmCode* asmCode, LabelsTable* labelsTable);
    Error getCommandArg(const Line* line, int* shift, AsmCode_t* argType, AsmCode_t* argValue, LabelsTable* labelsTable);
    Error translateLineArgs(Line* asmTextLine, const int commandNameLength, AsmCode* asmCode, LabelsTable* labelsTable);

    /**
     * @brief Translate asm text to asm code
     *
     * @param [in] asmText Asm text
     * @param [out] asmCode Asm code
     * @return Error Error code
     */
    Error translate(ListOfLines* asmText, AsmCode* asmCode, LabelsTable* labelsTable) {
        assert(asmText != nullptr);
        assert(asmCode != nullptr);
        assert(asmText->size != 0);

        if (asmCode->code == nullptr) {
            asmCode::createBuf(asmCode);
        }
        asmCode->pc = 0;

        for (int lineI = 0; lineI < asmText->size; ++lineI) {
            // printf("%s\n", asmText->lines[lineI].str);

            Error translationRes = translateLine(&asmText->lines[lineI], asmCode, labelsTable);
            switch (translationRes) {
            case Error::BROKEN_ASMTEXT:
            case Error::OVERFLOW_BY_NAME:
            case Error::UNKNOWN_COMMAND:
            case Error::COMMAND_SYNTAX:
                printf("Line %d:", lineI);
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
    Error getCommandArg(const Line* line, int* shift, AsmCode_t* argType, AsmCode_t* argValue, LabelsTable* labelsTable) {
        assert(line != nullptr);
        assert(shift != nullptr);
        assert(argType != nullptr);
        assert(argValue != nullptr);
        assert(argType != argValue);
        if (*shift > line->lenght)
            return Error::BROKEN_ASMTEXT;

        *argType = classifyArg(line->str[*shift]);
        // if (*argType == null)
            // return Error::BROKEN_ASMTEXT;

        int scanfRes = 0;
        switch (*argType) {

        case asmLang::COMMAND_ARG_HAS_I:
            // scanfRes = sscanf_s(line->str + *shift, "%" SCNu8, argValue);
            // scanfRes = sscanf_s(line->str + *shift, "%hhu", argValue);
            scanfRes = strAsmLang::sscanAsmCode_t(line->str + *shift, argValue);
            if (scanfRes != 1)
                return Error::COMMAND_SYNTAX;

            switch (strAsmLang::skipSymbols(line, shift, strAsmLang::isCorrectSymbI)) {
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
            strAsmLang::skipSymbols(line, shift, strAsmLang::isCorrectSymbM);
            break;

        case null: // LABEL
            *argType = asmLang::COMMAND_ARG_HAS_I;
            *argValue = (AsmCode_t) labelsTable::getLabelPC(labelsTable, line->str + *shift, line->lenght - *shift);
            break;

        default:
            assert(0 && "classifyArg()'s result is not a correct code");
        }

        return Error::OK;
    }

    Error translateLineArgs(Line* asmTextLine, const int commandNameLength, AsmCode* asmCode, LabelsTable* labelsTable) {
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
            Error getArgRes = getCommandArg(asmTextLine, &strShift, &argCode, &arg, labelsTable);

            if (getArgRes)
                return getArgRes;

            if (argCode != asmLang::COMMAND_ARG_HAS_M) {
                if ((gotArgs & argCode))
                    return Error::COMMAND_SYNTAX;
                asmCode::add(asmCode, arg);
            }
            gotArgs |= argCode;
            *commandPtr |= argCode;
        }

        return Error::OK;
    }

    Error translateLine(Line* asmTextLine, AsmCode* asmCode, LabelsTable* labelsTable) {
        assert(asmTextLine != nullptr);
        assert(asmCode != nullptr);

        char commandName[COMNAME_BUFFER_SIZE] = {};
        int commandNameLength = 0;

        strAsmLang::Error getCommandNameRes = getCommandName(asmTextLine, commandName, &commandNameLength, COMNAME_BUFFER_SIZE);
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

        if (isNameLabel(commandName, commandNameLength)) {
            labelsTable::setLabel(labelsTable, commandName, commandNameLength, asmCode->pc);

            return Error::OK;
        }

#define DESCRIPT_COMMAND(name, code, ...) \
        if (!strcmp(commandName, name)) {  \
            asmCode::add(asmCode, code);    \
        } else
#include <..\asmLangDSLInstructions.cpp>
        /* ...else */ {
            return Error::UNKNOWN_COMMAND;
        }
#undef DESCRIPT_COMMAND
        /*if (!strcmp(commandName, asmLang::COMMAND_HALT_NAME)) {
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
        }*/

        Error argsTranslationRes = Error::OK;
        argsTranslationRes = translateLineArgs(asmTextLine, commandNameLength, asmCode, labelsTable);

        return argsTranslationRes;
    }
}
