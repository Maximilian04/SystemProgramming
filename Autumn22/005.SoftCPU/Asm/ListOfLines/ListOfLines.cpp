#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys\stat.h>

#include "ListOfLines.h"

namespace listOfLines {
    _off_t getSizeOfFile(const char* fileName);
    size_t readFileToBuffer(const char* fileName, char** buffer);
    void replaceSymbol(ListOfLines* listPtr, size_t bufferSize, char bad, char good);
    size_t countLinesInBuffer(const char* buffer, size_t bufferSize);
    size_t getRidOfSpaces(ListOfLines* listPtr, size_t bufferSize);

    /**
     * @brief Get the size of file
     *
     * @param [in] fileName Name of file
     * @return _off_t Size of file or 0 if error
     */
    _off_t getSizeOfFile(const char* fileName) {
        assert(fileName != nullptr);

        struct stat fileStat = {};

        int statResult = stat(fileName, &fileStat);
        if (statResult != 0)
            return 0;
        assert(statResult == 0 && "Cannot get file info");

        return fileStat.st_size;
    }

    /**
     * @brief Read the whole file to buffer
     *
     * @note Need nullptr-ed buffer
     * @note Need free() for buffer
     *
     * @param [in] fileName Name of file
     * @param [out] buffer Pointer to pointer to place with buffer
     * @return size_t Size of buffer or 0 if error
     */
    size_t readFileToBuffer(const char* fileName, char** buffer) {
        assert(fileName != nullptr);
        assert(buffer != nullptr);

        assert((*buffer) == nullptr);

        int fileSize = getSizeOfFile(fileName);
        if (fileSize == 0)
            return 0;

        FILE* file = fopen(fileName, "rt");
        assert(file != nullptr && "Cannot open file");
        if (file == nullptr)
            return 0;

        (*buffer) = (char*)calloc(fileSize + 1, sizeof(char));
        assert((*buffer) != nullptr);

        size_t freadResult = fread((*buffer), sizeof(char), fileSize, file);
        fclose(file);

        (*buffer) = (char*)realloc((void*)(*buffer), sizeof(char) * (freadResult + 1));
        (*buffer)[freadResult] = '\0';

        return freadResult + 1;
    }

    /**
     * @brief Replace specific character in ListOfLines and separates lines
     *
     * @param [out] listPtr Struct with buffer
     * @param [in] bufferSize Size of buffer
     * @param [in] bad Character to be replaced
     * @param [in] good Cheracter to replace with
     */
    void replaceSymbol(ListOfLines* listPtr, size_t bufferSize, char bad, char good) {
        assert(listPtr != nullptr);

        do {
            listPtr->lines[listPtr->size].str = listPtr->firstVacant;
            listPtr->lines[listPtr->size].lenght = 0;

            while (true) {
                int* indexPtr = &listPtr->lines[listPtr->size].lenght;
                char* symbPtr = &listPtr->lines[listPtr->size].str[*indexPtr];

                if (*symbPtr == bad) {
                    *symbPtr = good;
                }
                if (*symbPtr == '\0') {
                    break;
                }
                (*indexPtr)++;
            }

            listPtr->firstVacant += listPtr->lines[listPtr->size].lenght + 1;
            if (listPtr->lines[listPtr->size].lenght == 0) {
                continue;
            }
            listPtr->size++;
        } while (listPtr->firstVacant < (listPtr->lines[0].str + bufferSize));
    }

    /**
     * @brief Count number of this symbol in buffer
     *
     * @param [in] buffer Buffer of chars
     * @param [in] bufferSize Size of buffer
     * @param [in] symb Symbol to compare with
     * @return size_t Count of symbols
     */
    size_t countLinesInBuffer(const char* buffer, const size_t bufferSize) {
        assert(buffer != nullptr);

        size_t linesCounter = 0;
        for (size_t i = 0; i < bufferSize; ++i) {
            if (buffer[i] == '\0' ||
                buffer[i] == '\n') {
                ++linesCounter;
            }
        }

        return linesCounter;
    }

    /**
     * @brief Upload ListOfLines from file
     *
     * @param [out] listPtr ListOFLines
     * @param [in] fileName File name
     * @return int 1 if file cannot be opened
     */
    int uploadList(ListOfLines* listPtr, const char* fileName, bool doGetRidOfSpaces) {
        assert(listPtr != nullptr);
        assert(fileName != nullptr);
        assert(listPtr->size == 0);
        assert(listPtr->lines == nullptr);

        size_t bufferSize = readFileToBuffer(fileName, &listPtr->firstVacant);
        if (bufferSize == 0) {
            return 1;
        }

        size_t tempCountOfLines = countLinesInBuffer(listPtr->firstVacant, bufferSize);
        listPtr->lines = (Line*)calloc(tempCountOfLines, sizeof(Line));
        assert(listPtr->lines != nullptr);
        listPtr->size = 0;

        replaceSymbol(listPtr, bufferSize, '\n', '\0');

        if (doGetRidOfSpaces) {
            bufferSize = getRidOfSpaces(listPtr, bufferSize);
        }

        assert(tempCountOfLines >= (size_t)listPtr->size);
        listPtr->lines = (Line*)realloc(listPtr->lines, sizeof(Line) * listPtr->size);
        assert(listPtr->lines != nullptr);

        return 0;
    }

    /**
     * @brief Bring string to correct form
     * 
     * @param [out] listPtr ListOfLines
     * @param [in] bufferSize Size of list's continious buffer
     * @return size_t New used buffer size
     */
    size_t getRidOfSpaces(ListOfLines* listPtr, size_t bufferSize) {
        assert(listPtr != nullptr);

        int lineCounter = 0;
        size_t shiftCounter = 0;

        size_t readSymbolIndex = 0;
        size_t writeSymbolIndex = 0;
        bool allowedSpace = false;
        bool prefixSpaces = true;

        for (; readSymbolIndex < bufferSize;) {
            if (listPtr->lines[0].str[readSymbolIndex] == ' ') {
                if (allowedSpace) {
                    allowedSpace = false;
                } else {
                    ++readSymbolIndex;
                    continue;
                }
            } else if (listPtr->lines[0].str[readSymbolIndex] == '\0') {
                allowedSpace = false;
                prefixSpaces = true;

                if (lineCounter > 0)
                    listPtr->lines[lineCounter].str = listPtr->lines[lineCounter - 1].str + listPtr->lines[lineCounter - 1].lenght + 1;
                
                listPtr->lines[lineCounter].lenght -= (int)(readSymbolIndex - writeSymbolIndex - shiftCounter);
                shiftCounter = readSymbolIndex - writeSymbolIndex;

                ++lineCounter;
            } else {
                if (prefixSpaces) {
                    prefixSpaces = false;
                    allowedSpace = true;
                }
            }

            listPtr->lines[0].str[writeSymbolIndex] = listPtr->lines[0].str[readSymbolIndex];
            ++readSymbolIndex;
            ++writeSymbolIndex;
        }

        return writeSymbolIndex;
    }

    /**
     * @brief Free memory used with ListOfLines
     *
     * @param listPtr Pointer to ListOfLines
     */
    void destroyList(ListOfLines* listPtr) {
        assert(listPtr != nullptr);

        free(listPtr->lines[0].str);
        free(listPtr->lines);
    }
}
