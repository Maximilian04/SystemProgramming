#include <stdio.h>
#include <assert.h>

#include "cyrillicString.h"

#include "pervert.h"

const char FILE_NAME[] = "EvgeniyOnegin.txt";
const char FILE_ALPH_NAME[] = "alphabet.txt";
const char FILE_OUT_NAME[] = "build\\PunyEvgeniyOnegin.txt";

namespace pervert {
    int cmpLinesRealNum(const void* a, const void* b); ///< Compare via comparing pointers

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
     */
    void uploadPoem() {
        listOfLines::uploadList(&linesOfPoem, FILE_NAME);
    }

    /**
     * @brief Upload cyrillic alphabet from file
     *
     */
    void uploadAlphabet() {
        listOfLines::uploadList(&linesOfAlphabet, FILE_ALPH_NAME);
        cyrillicString::setAlphabet(&linesOfAlphabet);
    }

    /**
     * @brief Open output file
     *
     */
    void openOutFile() {
        assert(outFile == nullptr);
        outFile = fopen(FILE_OUT_NAME, "wt");
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
     * @brief Free memory used by linesOfAlphabet
     *
     */
    void destroyAlphabet() {
        listOfLines::destroyList(&linesOfAlphabet);
    }
}
