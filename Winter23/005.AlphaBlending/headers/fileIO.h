/**
 * @file fileIO.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief Files I/O
 * @date 2022-04-15
 */

#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>

const size_t BUFFERSIZE = 64;
const char CONFIGNAME[] = "xconfig.txt";

int openImages(FILE** bgrPtr, FILE** frtPtr);

#endif // FILEIO_H
