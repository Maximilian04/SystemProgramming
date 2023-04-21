#include "hack.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys\stat.h>

const size_t MASKSIZE = 5;
const uint8_t SEARCHMASK[MASKSIZE] = { 0x3D, 0x01, 0x00, 0x75, 0x03 };
const uint8_t    FIXMASK[MASKSIZE] = { 0xB8, 0x01, 0x00, 0x74, 0x03 };

void upgradeCom(char const name[]) {
    if (!name) return;

    FILE* file = fopen(name, "rb");
    if (file == nullptr) return;

    char* buffer = nullptr;
    size_t bufSize = 100;
    buffer = (char*)calloc(bufSize, 1);

    int counter = 0;

    size_t index = 0;
    for (index = 0; true; ++index) {
        if (index == bufSize - 1) {
            bufSize *= 2;
            buffer = (char*)realloc(buffer, bufSize);
        }

        int in = fgetc(file);
        if (in == EOF) break;

        buffer[index] = (char)in;

        if (index < MASKSIZE) continue;

        bool correctMask = true;
        for (size_t offset = 0; offset < MASKSIZE; ++offset) {
            if (buffer[index + offset - MASKSIZE] != SEARCHMASK[offset]) correctMask = false;
        }

        if (!correctMask) continue;
        ++counter;
        for (size_t offset = 0; offset < MASKSIZE; ++offset) {
            buffer[index + offset - MASKSIZE] = FIXMASK[offset];
        }
    }

    fclose(file);


    file = nullptr;
    file = fopen(name, "wb");
    if (file == nullptr) return;

    for (size_t wrIndex = 0; wrIndex < index; ++wrIndex) {
        fputc(buffer[wrIndex], file);
    }

    fclose(file);

    printf("fixed %d occurences\n", counter);

    free(buffer);
}
