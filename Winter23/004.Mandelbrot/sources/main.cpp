#include "include.h"

int main() {
    if (WINSIZEX % BOOST_F) {
        printf("BOOST DIVISIBILITY!!!\n");
        return 1;
    }

    Mat image(WINSIZEY, WINSIZEX, CV_8UC3);
    imshow(WINNAME, image);

    clock_t timer = clock();

    int key = 0;
    while (key != 27) {
        drawM(image);

        double spf = ((double)(-timer) + (timer = clock())) / CLOCKS_PER_SEC;
        char fpsS[10] = {};
        sprintf(fpsS, "%f", 1 / spf);
        putText(image, fpsS, Point(0, 25), cv::FONT_HERSHEY_DUPLEX, 1.0, textColor, 2);

        imshow(WINNAME, image);
        key = waitKey(1);
    }

    printf("Program finished 0\n");
    return 0;
}
