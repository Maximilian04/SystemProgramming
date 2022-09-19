#include <stdio.h>
#include <assert.h>

#include "cyrillicString.h"

#include "pervert.h"

const char* fileName     = "EvgeniyOnegin.txt";
const char* fileAlphName = "alphabet.txt";
const char* fileOutName  = "build\\PunyEvgeniyOnegin.txt";

namespace pervert {
    int cmpLinesRealNum(const void* a, const void* b); ///< Compare via comparing pointers
    void printHelpMessage();

    ListOfLines linesOfPoem     = { nullptr, nullptr, 0 };
    ListOfLines linesOfAlphabet = { nullptr, nullptr, 0 };
    FILE* outFile = nullptr; ///< File for output

    /**
     * @brief Sort lines with its beginning
     *
     */
    void sortLinesBeginning() {
        //qsort(linesOfPoem.lines, linesOfPoem.size, sizeof(Line), cmpLines);
        uq_sort(linesOfPoem.lines, 0, linesOfPoem.size - 1, cyrillicString::cmpLines, sizeof(Line));
    }

    int cmpLinesRealNum(const void* a, const void* b) {
        if (((const Line*)a)->str < ((const Line*)b)->str) {
            return -1;
        }
        if (((const Line*)a)->str > ((const Line*)b)->str) {
            return 1;
        }
        return 0;
    }

    /**
     * @brief Sort lines with its number in raw poem
     *
     */
    void sortLinesReal() {
        //qsort(linesOfPoem.lines, linesOfPoem.size, sizeof(Line), cmpLinesRealNum);
        uq_sort(linesOfPoem.lines, 0, linesOfPoem.size - 1, cmpLinesRealNum, sizeof(Line));
    }

    /**
     * @brief Sort lines with its ending
     *
     */
    void sortLinesEnding() {
        //qsort(linesOfPoem.lines, linesOfPoem.size, sizeof(Line), cmpLinesBack);
        uq_sort(linesOfPoem.lines, 0, linesOfPoem.size - 1, cyrillicString::cmpLinesBack, sizeof(Line));
    }

    /**
     * @brief Prints listOfLines to output in current state
     *
     */
    void writeOutPoem() {
        for (int listI = 0; listI < linesOfPoem.size; ++listI) {
            fprintf(outFile, "%s\n", linesOfPoem.lines[listI].str);
        }
    }

    /**
     * @brief Read linesOfPoem from file
     *
     * @return int 1 if file cannot be opened
     */
    int uploadPoem() {
        int result = listOfLines::uploadList(&linesOfPoem, fileName);
        if (result) {
            printf("Cannot open poem file");
            return 1;
        }
        return 0;
    }

    /**
     * @brief Upload cyrillic alphabet from file and set cyrillicString::setAlphabet
     *
     * @return int 1 if file cannot be opened
     */
    int uploadAlphabet() {
        int result = listOfLines::uploadList(&linesOfAlphabet, fileAlphName);
        if (result) {
            printf("Cannot open alphabet file");
            return 1;
        }
        cyrillicString::setAlphabet(&linesOfAlphabet);

        return 0;
    }

    /**
     * @brief Open output file
     *
     */
    void openOutFile() {
        assert(outFile == nullptr);
        outFile = fopen(fileOutName, "wt");
        assert(outFile != nullptr);
    }

    /**
     * @brief Close output file
     *
     */
    void closeOutFile() {
        assert(outFile != nullptr);
        fclose(outFile);
    }

    /**
     * @brief Free memory used by poem and alphabet
     *
     */
    void destroyAll() {
        destroyPoem();
        destroyAlphabet();
    }

    /**
     * @brief Free memory used by linesOfPoem
     *
     */
    void destroyPoem() {
        listOfLines::destroyList(&linesOfPoem);
    }

    /**
     * @brief Free memory used by linesOfAlphabet and set cyrillicString::setAlphabet to nullptr
     *
     */
    void destroyAlphabet() {
        listOfLines::destroyList(&linesOfAlphabet);
        cyrillicString::setAlphabet(nullptr);
    }

    /**
     * @brief Prints help message to console
     *
     */
    void printHelpMessage() {
        printf(
            "Help message. Command list:\n"
            "-h\t\tshow help message\n"
            "-f [name]\tget mutable poem from [name] file\n"
            "-o [name]\twrite program output to [name] file\n"
            "-a [name]\tget mutable alphabet from [name] file\n");
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
        assert(userdata == nullptr);

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
            case 'f':
                if (!cmdArguments[cmdFlagI].hasArgument) {
                    printf("Cannot recognize file name after '-f'. Please use flags from list below.\n");
                    printHelpMessage();
                    return cmdParser::ParserResult::BAD_INPUT;
                }

                fileName = cmdArguments[cmdFlagI].argument;

                break;
            case 'a':
                if (!cmdArguments[cmdFlagI].hasArgument) {
                    printf("Cannot recognize file name after '-f'. Please use flags from list below.\n");
                    printHelpMessage();
                    return cmdParser::ParserResult::BAD_INPUT;
                }

                fileAlphName = cmdArguments[cmdFlagI].argument;

                break;
            case 'o':
                if (!cmdArguments[cmdFlagI].hasArgument) {
                    printf("Cannot recognize file name after '-f'. Please use flags from list below.\n");
                    printHelpMessage();
                    return cmdParser::ParserResult::BAD_INPUT;
                }

                fileOutName = cmdArguments[cmdFlagI].argument;

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
