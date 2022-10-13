#include <assert.h>
#include <stdio.h>

#include "fileIO.h"

#include "ui.h"

namespace ui {
    static const char* outputFileName = nullptr;

    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata);
    void printHelpMessage();

    /**
     * @brief Struct for transfering information to cmdParser::processFlags
     *
     */
    typedef struct {
        const char* asmTextFileName;  ///< buffer with user's tests file's name
    } ProccessFlagsPtrs;

    /**
     * @brief Handle console flags & upload asmText
     *
     * @param [in] argc Console input
     * @param [in] argv Console input
     * @param [out] asmTextPtr Asm text
     * @return Error Error code
     */
    Error handleFlags(const int argc, const char* const* const argv, ListOfLines* asmTextPtr) {
        ProccessFlagsPtrs proccessFlagsPtrs = { nullptr };
        switch (cmdParser::handleFlags(argc, argv, &reactToFlags, &proccessFlagsPtrs)) {
        case cmdParser::ParserResult::BAD_INPUT:
            printf("F*U*SB Input error\n");
            return Error::FLAG_ERR;
            break;
        case cmdParser::ParserResult::GOOD_INPUT:
            break;
        default:
            assert(false && "cmdParser::processFlags()'s return is not a cmdParser::PARSER_RESULT's member");
        }

        if (proccessFlagsPtrs.asmTextFileName == nullptr) {
            printf("Please enter program code file name\n");
            return Error::FILE_ERR;
        }
        int uploadRes = listOfLines::uploadList(asmTextPtr, proccessFlagsPtrs.asmTextFileName, true);
        if (uploadRes != 0) {
            printf("F*U*B uploadList error\n");
            return Error::FILE_ERR;
        }

        return Error::OK;
    }

    /**
     * @brief Translate asm text to asm code
     *
     * @param [in] asmText Asm text
     * @param [out] asmCode Asm code
     * @return Error Error code
     */
    Error translateAsm(ListOfLines* asmText, AsmCode* asmCode) {
        switch (asmbler::translate(asmText, asmCode)) {
        case asmbler::Error::OK:
            break;
        case asmbler::Error::BROKEN_ASMTEXT:
            printf("Broken ListOfLines inside of translation\n");
            return Error::TRANS_ERR;
        case asmbler::Error::OVERFLOW_BY_NAME:
            printf("Incorrect file name (buffer was overflowed)\n");
            return Error::TRANS_ERR;
        case asmbler::Error::UNKNOWN_COMMAND:
            // printf("Line: %d, :%s\n", lineI, asmText->lines[lineI].str);
            printf("Syntax error: unknown command\n");
            return Error::SYNTAX;
        case asmbler::Error::COMMAND_SYNTAX:
            printf("Syntax error: incorrect command syntax\n");
            printf("\n");
            return Error::SYNTAX;
        default:
            assert(false && "asmbler::translate()'s return is not a asmbler::Error's member");
        }
        return Error::OK;
    }

    /**
     * @brief Write out machine code to file
     *
     * @param [in] asmCode Asm Code
     * @return Error Error code
     */
    Error writeAsmCode2File(AsmCode* asmCode) {
        fileIO::Error writingRes = fileIO::writeAsmCode2File(asmCode, nullptr);

        return Error::OK;
    }

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
     * @brief Function with list of reactions to all possible flags
     *
     * @note Also function open incoming stream as file or stdio
     *
     * @note Must be given to cmdParser::handleFlags
     *
     * @param [in] cmdFlagC Number of active flags
     * @param [in] cmdArguments Array of flags
     * @param [out] userdata Pointer to #ProccessFlagsPtrs casted to (void*)
     * @return cmdParser::ParserResult
     */
    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata) {
        assert(cmdArguments != nullptr);
        assert(userdata != nullptr);
        assert(((ProccessFlagsPtrs*)userdata)->asmTextFileName == nullptr);

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
            case 'i':
                if (!cmdArguments[cmdFlagI].hasArgument) {
                    printf("Cannot recognize file name after '-i'. Please use flags from list below.\n");
                    printHelpMessage();
                    return cmdParser::ParserResult::BAD_INPUT;
                }

                ((ProccessFlagsPtrs*)userdata)->asmTextFileName = cmdArguments[cmdFlagI].argument;
                break;
            case 'c':
                printf("F*U.\n");
                return cmdParser::ParserResult::BAD_INPUT;
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
}
