#include <assert.h>
#include <stdio.h>

#include "ui.h"

namespace ui {
    cmdParser::ParserResult reactToFlags(int cmdFlagC, cmdParser::CmdArgument* cmdArguments, void* userdata);
    void printHelpMessage();

    /**
     * @brief Struct for transfering information to cmdParser::processFlags
     *
     */
    typedef struct {
        const char* asmCodeFileName; ///< buffer with user's tests file's name
        CPU::MODE* cpuMode;          ///< cpu mode (cpu or disassembler)
    } ProccessFlagsPtrs;

    /**
     * @brief Handle console flags & upload asmText
     *
     * @param [in] argc Console input
     * @param [in] argv Console input
     * @param [out] asmTextPtr Asm text
     * @return Error Error code
     */
    Error handleFlags(const int argc, const char* const* const argv, CPU* cpuPtr) {
        ProccessFlagsPtrs proccessFlagsPtrs = { nullptr, &cpuPtr->mode };
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

        if (proccessFlagsPtrs.asmCodeFileName == nullptr) {
            printf("Please enter program file name\n");
            return Error::FILE_ERR;
        }
        FILE* file = fopen(proccessFlagsPtrs.asmCodeFileName, "rb");
        if (file == nullptr) {
            printf("Cannot open file\n");
            return Error::FILE_ERR;
        }


        size_t freadRes = fread(&cpuPtr->code.codeBufferSize, sizeof(size_t), 1, file);
        if (freadRes != 1 || cpuPtr->code.codeBufferSize > asmLang::MAX_CODE_SIZE) {
            printf("Incorrect file\n");
            return Error::FILE_ERR;
        }
        if (freadRes > cpuPtr->code.codeBufferSize) {
            printf("Incompatible file and CPU\n");
            return Error::CODE_SIZE;
        }
        freadRes = fread(cpuPtr->code.code, sizeof(uint8_t), cpuPtr->code.codeBufferSize, file);
        if (freadRes != cpuPtr->code.codeBufferSize) {
            printf("Incorrect file\n");
            return Error::FILE_ERR;
        }
        cpuPtr->code.pc = 0;

        fclose(file);

        return Error::OK;
    }

    /**
     * @brief Run program with CPU
     *
     * @param [in] mainCPU CPU object
     * @return Error Error code
     */
    Error runProgram(CPU* mainCPU) {
        switch (cpu::run(mainCPU)) {
        case cpu::Error::OK:
            break;
        case cpu::Error::UNKNOWN_COMMAND:
            printf("CPU Error: unknown command - program file is broken");
            return Error::UNKNOWN_COMMAND;
        case cpu::Error::UNREACHABLE_HLT:
            assert(false && "cpu::run() returned UNREACHABLE_HLT ???");
        case cpu::Error::OK_HALT:
            assert(false && "cpu::run() returned OK_HALT ???");
        default:
            assert(false && "cpu::run()'s return is not a cpu::Error's member");
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
            "-c\t\tallow you to enter code via console (in future, f*u)\n"
            "-d\t\tRun in deassembler mode\n");
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
        assert(((ProccessFlagsPtrs*)userdata)->asmCodeFileName == nullptr);

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

                ((ProccessFlagsPtrs*)userdata)->asmCodeFileName = cmdArguments[cmdFlagI].argument;
                break;
            case 'c':
                printf("F*U.\n");
                return cmdParser::ParserResult::BAD_INPUT;
                break;
            case 'd':
                *((ProccessFlagsPtrs*)userdata)->cpuMode = CPU::MODE::DISASSEMBLER;
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
