#include "include.h"

int main() {
    FILE* imgBgr = nullptr;
    FILE* imgFrt = nullptr;
    if (openImages(&imgBgr, &imgFrt)) {
        printf("Pictures error\n");
        return 1;
    }

    if (WINSIZEX % BOOST_F) {
        printf("BOOST DIVISIBILITY!!!\n");
        return 1;
    }

    Mat image(WINSIZEY, WINSIZEX, CV_8UC3);
    imshow(WINNAME, image);

    clock_t timer = clock();
    double averageFps = 0.;
    long frameCounter = 0;

    int key = 0;
    while (key != 27) {
        // drawM(image);

        double spf = ((double)(-timer) + (timer = clock())) / CLOCKS_PER_SEC;
        double fps = 1 / spf;

        averageFps += fps;
        ++frameCounter;

        char fpsS[10] = {};
        sprintf(fpsS, "%f", fps);
        putText(image, fpsS, Point(0, 25), cv::FONT_HERSHEY_DUPLEX, 1.0, textColor, 2);

        imshow(WINNAME, image);
        key = waitKey(1);
    }

    averageFps /= (double)frameCounter;
    FILE* logFile = fopen("logfps.txt", "a");
    // fprintf(logFile, "%s %f\n", getPrName(), averageFps);
    fclose(logFile);

    printf("Program finished 0\n");
    return 0;
}
