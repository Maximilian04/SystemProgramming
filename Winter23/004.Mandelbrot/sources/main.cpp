#include "include.h"

int main() {
    Mat image(WINSIZEY, WINSIZEX, CV_8UC3);
    imshow("mandelbrot", image);

    clock_t timer = clock();

    int key = 0;
    while (key != 27) {
        for (int32_t pxY = 0; pxY < WINSIZEY; ++pxY) {
            for (int32_t pxX = 0; pxX < WINSIZEX; ++pxX) {
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


        double spf = ((double)(-timer) + (timer = clock())) / CLOCKS_PER_SEC;
        char fpsS[10] = {};
        sprintf(fpsS, "%f", 1 / spf);
        putText(image, fpsS, Point(0, 25), cv::FONT_HERSHEY_DUPLEX, 1.0, textColor, 2);

        imshow("mandelbrot", image);
        key = waitKey(1);
    }


    printf("Program finished 0\n");
    return 0;
}
