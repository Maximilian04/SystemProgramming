#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

// #pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#include <opencv2/opencv.hpp>
// #include "D:/programming/libraries/opencv-4.6.0/opencv-build-release-freetype/install/include/opencv2/opencv.hpp"
// #pragma GCC diagnostic pop

using namespace cv;
using namespace std;

const int16_t WINSIZEX = 1000;
const int16_t WINSIZEY = 700;

float SCALE = 1.f / 400.0f; // [1/px]
float OFFSETX = -2.f;
float OFFSETY = -SCALE * WINSIZEY / 2.f;

const float INFRAD = 10.f;
const int16_t INFNUM = 700;

int main() {
    Mat image(WINSIZEY, WINSIZEX, CV_8UC3);
    imshow("mandelbrot", image);

    clock_t timer = clock();

    int key = 0;
    while (key != 27) {
        for (int16_t pxX = 0; pxX < WINSIZEX; ++pxX) {
            for (int16_t pxY = 0; pxY < WINSIZEY; ++pxY) {
                float ptX = OFFSETX + SCALE * pxX;
                float ptY = OFFSETY + SCALE * pxY;

                float vX = ptX;
                float vY = ptY;

                int16_t counter = 0;

                while (counter < INFNUM &&
                    vX < +INFRAD &&
                    vX > -INFRAD &&
                    vY < +INFRAD &&
                    vY > -INFRAD) {

                    float quadrX = vX * vX - vY * vY;
                    float quadrY = 2 * vX * vY;

                    vX = quadrX + ptX;
                    vY = quadrY + ptY;

                    ++counter;
                }

                if (counter == INFNUM) {
                    image.at<Vec3b>(pxY, pxX)[0] = 0;
                    image.at<Vec3b>(pxY, pxX)[1] = 0;
                    image.at<Vec3b>(pxY, pxX)[2] = 0;
                } else {
                    float factor = 1.0f - (float)counter / INFNUM;

                    image.at<Vec3b>(pxY, pxX)[0] = 0;
                    image.at<Vec3b>(pxY, pxX)[1] = (uint8_t)(256.f * pow(factor, 30));
                    image.at<Vec3b>(pxY, pxX)[2] = 0;
                }
            }
        }


        double spf = ((double)(-timer) + (timer = clock())) / CLOCKS_PER_SEC;
        char fpsS[10] = {};
        sprintf(fpsS, "%f", 1 / spf);
        putText(image, fpsS, Point(0, 25), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(118, 185, 0), 2);

        imshow("mandelbrot", image);
        key = waitKey(1);
    }


    printf("Program finished 0\n");
    return 0;
}
