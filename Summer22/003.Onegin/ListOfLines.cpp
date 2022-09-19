#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys\stat.h>

#include "ListOfLines.h"

namespace listOfLines {
    _off_t getSizeOfFile(const char* fileName);
    size_t readFileToBuffer(const char* fileName, char** buffer);
    void replaceSymbol(ListOfLines* listPtr, size_t bufferSize, char bad, char good);

    _off_t getSizeOfFile(const char* fileName) {
        struct stat fileStat = {};

        int statResult = stat(fileName, &fileStat);
        assert(statResult == 0 && "Cannot get file info");

        return fileStat.st_size;
    }

    size_t readFileToBuffer(const char* fileName, char** buffer) {
        assert((*buffer) == nullptr);

        int fileSize = getSizeOfFile(fileName);

        FILE* file = fopen(fileName, "rt");
        assert(file != nullptr && "Cannot open file");

        (*buffer) = (char*)calloc(fileSize + 1, sizeof(char));
        assert((*buffer) != nullptr);

        size_t freadResult = fread((*buffer), sizeof(char), fileSize, file);
        fclose(file);

        (*buffer) = (char*)realloc((void*)(*buffer), sizeof(char) * (freadResult + 1));
        (*buffer)[freadResult] = '\0';

        return freadResult + 1;
    }

    void replaceSymbol(ListOfLines* listPtr, size_t bufferSize, char bad, char good) {
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

    void uploadList(ListOfLines* listPtr, const char* fileName) {
        assert(listPtr->size == 0);

        size_t bufferSize = readFileToBuffer(fileName, &listPtr->firstVacant);

        //printf("%d %d\n", (int)freadResult, (int)fileStat.st_size);

        listPtr->lines = (Line*)calloc(bufferSize, sizeof(Line));
        assert(listPtr->lines != nullptr);
        listPtr->size = 0;

        replaceSymbol(listPtr, bufferSize, '\n', '\0');

        //printf("%d\n", listPtr->size);
        listPtr->lines = (Line*)realloc(listPtr->lines, sizeof(Line) * listPtr->size);
    }

    void destroyList(ListOfLines* listPtr) {
        free(listPtr->lines[0].str);
        free(listPtr->lines);
    }
}
