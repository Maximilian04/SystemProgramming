#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "pervert.h"

const char FILE_NAME[] = "EvgeniyOnegin.txt";

namespace pervert {
    ListOfLines listOfLines = { {}, 0 };

    /**
     * @brief Read ListOfLines from file
     *
     */
    void readListOfLines() {
        assert(listOfLines.size == 0);
        listOfLines.lines = (Line*)calloc(MAX_LINE_NUMBER, sizeof(Line));

        FILE* file = fopen(FILE_NAME, "r");
        listOfLines.size = 0;
        while (listOfLines.size < MAX_LINE_NUMBER) {
            listOfLines.lines[listOfLines.size].str = (char*)calloc(EXTRA_BUFFER_SIZE, sizeof(char));
            int fscanfRes = fscanf(file, "%" EXTRA_BUFFER_SIZE_ "[^\n]", listOfLines.lines[listOfLines.size].str);
            fgetc(file);

            if (fscanfRes == EOF) {
                break;
            } else if (fscanfRes == 0) {
                continue;
            } else if (fscanfRes != 1) {
                assert(false && "fscanf returned ???");
            }

            listOfLines.lines[listOfLines.size].lenght = (int)strlen(listOfLines.lines[listOfLines.size].str);
            listOfLines.size++;
        }
        fclose(file);
        assert(listOfLines.size < MAX_LINE_NUMBER);

        printf("%d\n", listOfLines.size);
    }

    /**
     * @brief Free memory used by listOfLines
     *
     */
    void destroyListOfLines() {
        for (int i = 0; i < listOfLines.size; ++i) {
            free(listOfLines.lines[i].str);
        }
        free(listOfLines.lines);
    }
}
