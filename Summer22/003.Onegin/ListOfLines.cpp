#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys\stat.h>

#include "ListOfLines.h"

namespace listOfLines {
    void uploadList(ListOfLines* listPtr, const char* fileName) {
        assert(listPtr->size == 0);

        struct stat fileStat;

        int statResult = stat(fileName, &fileStat);
        FILE* file = fopen(fileName, "rt");
        assert(statResult == 0 && "Cannot get file info");
        assert(file != nullptr && "Cannot open file");

        listPtr->firstVacant = (char*)calloc(fileStat.st_size + 1, sizeof(char));
        size_t freadResult = fread(listPtr->firstVacant, sizeof(char), fileStat.st_size, file);
        listPtr->firstVacant = (char*)realloc((void*)listPtr->firstVacant, sizeof(char) * (freadResult + 1));
        listPtr->firstVacant[freadResult] = '\0';

        //printf("%d %d\n", (int)freadResult, (int)fileStat.st_size);

        listPtr->lines = (Line*)calloc(freadResult + 1, sizeof(Line));
        listPtr->size = 0;

        do {
            listPtr->lines[listPtr->size].str = listPtr->firstVacant;
            listPtr->lines[listPtr->size].lenght = 0;

            while (true) {
                int* indexPtr = &listPtr->lines[listPtr->size].lenght;
                char* symbPtr = &listPtr->lines[listPtr->size].str[*indexPtr];
                if (*symbPtr == '\n') {
                    *symbPtr = '\0';
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
        } while (listPtr->firstVacant < (listPtr->lines[0].str + freadResult + 1));

        fclose(file);

        //printf("%d\n", listPtr->size);
        listPtr->lines = (Line*)realloc(listPtr->lines, sizeof(Line) * listPtr->size);
    }

    void destroyList(ListOfLines* listPtr) {
        free(listPtr->lines[0].str);
        free(listPtr->lines);
    }
}
