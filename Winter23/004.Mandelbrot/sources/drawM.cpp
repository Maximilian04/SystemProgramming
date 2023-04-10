#include "include.h"

const char WINNAME[] = "mandelbrot";
const int32_t BOOST_F = 1;

void drawM(Mat image) {
    for (int32_t pxY = 0; pxY < WINSIZEY; ++pxY) {
        for (int32_t pxX = 0; pxX < WINSIZEX; ++pxX) {
            for (int i = 0; i < 10; ++i) {
            float ptX = OFFSETX + SCALE * pxX;
            float ptY = OFFSETY + SCALE * pxY;

            float vX = ptX;
            float vY = ptY;

            float vAbsQuadr = 0;

            int32_t counter = 0;

            while (counter < INFNUM &&
                (isfinite(vAbsQuadr) && vAbsQuadr <= (INFRAD * INFRAD))) {

                float quadrX = vX * vX - vY * vY;
                float quadrY = 2 * vX * vY;

                vX = quadrX + ptX;
                vY = quadrY + ptY;

                vAbsQuadr = vX * vX + vY * vY;

                ++counter;
            }

            if (i == 1)
            if (counter == INFNUM) {
                image.at<Vec3b>(pxY, pxX)[0] = 0;
                image.at<Vec3b>(pxY, pxX)[1] = 0;
                image.at<Vec3b>(pxY, pxX)[2] = 0;
            } else {
                float factor = 1.0f - (float)counter / INFNUM;

                image.at<Vec3b>(pxY, pxX)[0] = 50;
                image.at<Vec3b>(pxY, pxX)[1] = (uint8_t)(255.f * pow(factor, FACTORPOW));
                image.at<Vec3b>(pxY, pxX)[2] = 255;
            }
            }
        }
    }
}