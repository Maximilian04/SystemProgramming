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

uint8_t* readImage(FILE* file, const int32_t WINSIZEX, const int32_t WINSIZEY, size_t COMMON_BYTECOUNT, ImageMode mode = ImageMode::BACKGROUND);

#endif // FILEIO_H
