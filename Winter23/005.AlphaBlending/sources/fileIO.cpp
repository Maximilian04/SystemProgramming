#include "fileIO.h"
#include "coord2index.cpp"

static const WORD CORRECT_BFTYPE = 19778;
static const WORD CORRECT_BGRBIT = 24;
static const WORD CORRECT_FRTBIT = 32;

int openImage(FILE* config, FILE** dstPtr);

int openImages(FILE** bgrPtr, FILE** frtPtr) {
    FILE* config = fopen(CONFIGNAME, "r");
    if (!config) return 1;

    if (openImage(config, bgrPtr)) return 2;
    if (openImage(config, frtPtr)) return 2;

    if (fclose(config)) return 1;

    return 0;
}

void closeImages(FILE** bgrPtr, FILE** frtPtr) {
    fclose(*bgrPtr);
    *bgrPtr = nullptr;
    fclose(*frtPtr);
    *frtPtr = nullptr;
}

#define WIDTH     (bmInfo.bmiHeader.biWidth)
#define HEIGHT    (bmInfo.bmiHeader.biHeight)
#define BITCOUNT  (bmInfo.bmiHeader.biBitCount)
#define BYTECOUNT (bmInfo.bmiHeader.biBitCount / 8)

uint8_t* readImage(FILE* file, const int32_t WINSIZEX, const int32_t WINSIZEY, size_t COMMON_BYTECOUNT, ImageMode mode) {
    BITMAPFILEHEADER bmHeader;// = { 0, 0, 0, 0, 0 }
    BITMAPINFO bmInfo; // = 0
    fread(&bmHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&bmInfo, sizeof(BITMAPINFO), 1, file);

    if (bmHeader.bfType != CORRECT_BFTYPE) {
        return nullptr;
    }

    switch (mode) {
    case ImageMode::BACKGROUND:
        if (bmInfo.bmiHeader.biBitCount != CORRECT_BGRBIT) return nullptr;
        break;
    case ImageMode::BLENDABLE:
        if (bmInfo.bmiHeader.biBitCount != CORRECT_FRTBIT) return nullptr;
        break;
    default:
        return nullptr;
    }

    size_t bytewidth = WIDTH * BYTECOUNT;
    if (bytewidth % 4) bytewidth += 4 - bytewidth % 4;

    fseek(file, bmHeader.bfOffBits, SEEK_SET);


    size_t dataTSize = HEIGHT * bytewidth;
    size_t dataSize = WINSIZEX * WINSIZEY * COMMON_BYTECOUNT;
    uint8_t* dataT = (uint8_t*)calloc(dataTSize, 1);
    uint8_t* data = (uint8_t*)calloc(dataSize, 1);
    if (!data || !dataT) return nullptr;

    fread(dataT, 1, dataTSize, file);

    if (WINSIZEX > WIDTH ||
        WINSIZEY > HEIGHT) return nullptr;


    for (size_t y = 0; y < (size_t)WINSIZEY; ++y) {
        for (size_t x = 0; x < (size_t)WINSIZEX; ++x) {
            for (size_t c = 0; c < (size_t)BYTECOUNT; ++c) {
                // data[(WINSIZEX * y + x) * COMMON_BYTECOUNT + c] = dataT[bytewidth * (HEIGHT - y - 1) + x * BYTECOUNT + c];
                data[COORD2INDEX(x, y, WINSIZEX, WINSIZEY, COMMON_BYTECOUNT) + c] = dataT[bytewidth * (HEIGHT - y - 1) + x * BYTECOUNT + c];
            }
            for (size_t c = BYTECOUNT; c < (size_t)COMMON_BYTECOUNT; ++c) {
                // data[(WINSIZEX * y + x) * COMMON_BYTECOUNT + c] = 0; // 255
                data[COORD2INDEX(x, y, WINSIZEX, WINSIZEY, COMMON_BYTECOUNT) + c] = 0; // 255
            }
        }
    }

    free(dataT);
    return data;
}

#undef WIDTH
#undef HEIGTH
#undef BITCOUNT
#undef BYTECOUNT

int openImage(FILE* config, FILE** dstPtr) {
    char name[BUFFERSIZE] = { 0 };
    if (fscanf(config, "%s", name) != 1) return 1;

    *dstPtr = fopen(name, "rb");
    if (!*dstPtr) return 2;

    return 0;
}
