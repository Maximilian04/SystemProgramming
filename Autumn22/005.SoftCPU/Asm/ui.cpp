#include <assert.h>
#include <stdio.h>

#include "ui.h"

namespace ui {
    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata);
    void printHelpMessage();
    FILE* openFile(const char* const fileName);

    static FILE* asmInputFile = nullptr;

    /**
     * @brief Handle console flags
     *
     * @param [in] argc Console input
     * @param [in] argv Console input
     * @return Error Error code
     */
    Error handleFlags(const int argc, const char* const* const argv) {
        ProccessFlagsPtrs proccessFlagsPtrs = { &asmInputFile };
        switch (cmdParser::handleFlags(argc, argv, &reactToFlags, &proccessFlagsPtrs)) {
        case cmdParser::ParserResult::BAD_INPUT:
            return Error::FLAG_ERR;
            break;
        case cmdParser::ParserResult::GOOD_INPUT:
            break;
        default:
            assert(false && "cmdParser::processFlags()'s return is not a cmdParser::PARSER_RESULT's member");
            break;
        }
        return Error::FLAG_ERR;
    }

    /**
     * @brief Close input program file
     * 
     * @return Error Error code
     */
    Error closeInputFile() {
        int res = fclose(asmInputFile);
        if (res != 0) {
            return Error::FILE_ERR;
        }

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

                *((ProccessFlagsPtrs*)userdata)->testFilePtr = openFile(cmdArguments[cmdFlagI].argument);
                if (*((ProccessFlagsPtrs*)userdata)->testFilePtr == nullptr) {
                    printf("Cannot open program file correctly\n");
                    return cmdParser::ParserResult::BAD_INPUT;
                }
                break;
            case 'c':
                *((ProccessFlagsPtrs*)userdata)->testFilePtr = stdin;
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

    FILE* openFile(const char* const fileName) {
        assert(fileName != nullptr);

        FILE* file = fopen(fileName, "rt");
        return file;
    }
}
