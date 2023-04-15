#include "fileIO.h"

int openImage(FILE* config, FILE** dstPtr);

int openImages(FILE** bgrPtr, FILE** frtPtr) {
    FILE* config = fopen(CONFIGNAME, "r");
    if (!config) return 1;

    if (openImage(config, bgrPtr)) return 2;
    if (openImage(config, frtPtr)) return 2;

    if (fclose(config)) return 1;

    return 0;
}

int openImage(FILE* config, FILE** dstPtr) {
    char name[BUFFERSIZE] = { 0 };
    if (fscanf(config, "%s", name) != 1) return 1;

    *dstPtr = fopen(name, "rb");
    if (!*dstPtr) return 2;

    return 0;
}
