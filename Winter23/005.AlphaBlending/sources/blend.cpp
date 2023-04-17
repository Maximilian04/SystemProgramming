#include "include.h"
#include "getPrName.cpp"
#include "coord2index.cpp"

const char WINNAME[] = "alphaBlending";
const int32_t BOOST_F = 1;

void calcBlending(uint8_t* dst, const uint8_t* bgr, const uint8_t* frt);

void calcBlending(uint8_t* dst, const uint8_t* bgr, const uint8_t* frt) {
    uint16_t alpha = frt[3];
    uint16_t alphaRev = (uint16_t)(255 - alpha);

    for (int c = 0; c < 3; ++c) {
        dst[c] = uint8_t(
            (alphaRev * bgr[c] + alpha * frt[c]) >> 8
        );
    }
}

#define OFFSET COORD2INDEX(pxX, pxY, WINSIZEX, WINSIZEY, BYTECOUNT)

void blend(Mat image, const uint8_t* imgBgr, const uint8_t* imgFrt) {
    for (int32_t pxY = 0; pxY < WINSIZEY; ++pxY) {
        for (int32_t pxX = 0; pxX < WINSIZEX; ++pxX) {

#ifdef MULTIPLY
            for (int32_t i = 0; i < MULTIPLY; ++i)
#endif
                calcBlending(image.data + OFFSET, imgBgr + OFFSET, imgFrt + OFFSET);
        }
    }
}

#undef OFFSET
