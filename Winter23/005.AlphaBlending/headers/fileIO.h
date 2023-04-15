/**
 * @file fileIO.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Files I/O
 * @date 2022-04-15
 */

#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <windows.h>
#include <wingdi.h>
#include <stdint.h>
#include <stdlib.h>

const size_t BUFFERSIZE = 64;
const char CONFIGNAME[] = "xconfig.txt";

int openImages(FILE** bgrPtr, FILE** frtPtr);
void closeImages(FILE** bgrPtr, FILE** frtPtr);

enum ImageMode {
    BACKGROUND = 0,
    BLENDABLE,
};

struct ImageSize {
    size_t sizeX;
    size_t sizeY;
};

uint8_t* readImage(FILE* file, ImageSize* sizePtr, ImageMode mode = ImageMode::BACKGROUND);

#endif // FILEIO_H
