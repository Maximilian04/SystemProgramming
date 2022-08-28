#include <stdio.h>

#include "pervert.h"

int main() {
    pervert::uploadAlphabet();

    pervert::readListOfLines();
    pervert::openOutFile();

    pervert::sortLinesBeginning();
    pervert::writeOutPoem();
    pervert::sortLinesReal();
    pervert::writeOutPoem();
    pervert::sortLinesEnding();
    pervert::writeOutPoem();

    pervert::closeOutFile();
    pervert::destroyListOfLines();

    return 0;
}
