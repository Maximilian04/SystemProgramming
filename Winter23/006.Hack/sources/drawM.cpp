#include "include.h"
#include "getPrName.cpp"

const char WINNAME[] = "mandelbrot";
const int32_t BOOST_F = 1;

void calcMandelbrotP(int32_t pxY, int32_t pxX, int32_t* counterPtr);

void calcMandelbrotP(int32_t pxY, int32_t pxX, int32_t* counterPtr) {
    float ptX = OFFSETX + SCALE * (float)pxX;
    float ptY = OFFSETY + SCALE * (float)pxY;

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

    *counterPtr = counter;
}

void drawM(Mat image) {
    for (int32_t pxY = 0; pxY < WINSIZEY; ++pxY) {
        for (int32_t pxX = 0; pxX < WINSIZEX; ++pxX) {

            int32_t counter = 0;
#ifdef MULTIPLY
            for (int32_t i = 0; i < MULTIPLY; ++i)
                calcMandelbrotP(pxY, pxX, &counter);
#else
            calcMandelbrotP(pxY, pxX, &counter);
#endif


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
