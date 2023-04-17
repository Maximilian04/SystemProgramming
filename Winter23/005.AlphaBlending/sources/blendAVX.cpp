#include "include.h"
#include "getPrName.cpp"
#include "coord2index.cpp"

const char WINNAME[] = "alphaBlendingAVX";
const int32_t BOOST_F = 8;

void calcBlending(uint8_t* dst, const uint8_t* bgr, const uint8_t* frt);

void calcBlending(uint8_t* dst, const uint8_t* bgr, const uint8_t* frt) {
    float alpha = (float)frt[4] / 255.f;

    for (int c = 0; c < 3; ++c) {
        dst[c] = uint8_t(alpha * bgr[c] + (1 - alpha) * frt[c]);
    }
}

#define OFFSET COORD2INDEX(pxX, pxY, WINSIZEX, WINSIZEY, BYTECOUNT)

void blend(Mat image, const uint8_t* imgBgr, const uint8_t* imgFrt) {
    for (int32_t pxY = 0; pxY < WINSIZEY; ++pxY) {
        for (int32_t pxX = 0; pxX < WINSIZEX; pxX += BOOST_F) {

#ifdef MULTIPLY
            for (int32_t i = 0; i < MULTIPLY; ++i)
#endif
                calcBlending(image.data + OFFSET, imgBgr + OFFSET, imgFrt + OFFSET);
        }
    }
}

#undef OFFSET
