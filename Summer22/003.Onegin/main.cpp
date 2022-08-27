#include <stdio.h>

#include "pervert.h"

int main() {
    pervert::uploadAlphabet();

    for (int i = 0; i < pervert::listOfAlphabet.size; ++i) {
        printf("%d\n", pervert::listOfAlphabet.lines[i].str[0]);
    }

    pervert::readListOfLines();
    pervert::openOutFile();

    pervert::sortLinesBeginning();
    pervert::writeOutPoem(pervert::WritingPos::BEGIN);

    pervert::closeOutFile();
    pervert::destroyListOfLines();

    return 0;
}
