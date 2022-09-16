#include <stdio.h>

#include "pervert.h"

int main() {
    pervert::uploadAlphabet();

    pervert::uploadPoem();
    pervert::openOutFile();

    pervert::sortLinesBeginning();
    pervert::writeOutPoem();
    pervert::sortLinesReal();
    pervert::writeOutPoem();
    pervert::sortLinesEnding();
    pervert::writeOutPoem();

    pervert::closeOutFile();
    pervert::destroyAll();

    return 0;
}
