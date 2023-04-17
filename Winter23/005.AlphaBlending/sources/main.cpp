#include "include.h"

int main() {
    FILE* fileBgr = nullptr;
    FILE* fileFrt = nullptr;
    if (openImages(&fileBgr, &fileFrt)) {
        printf("Pictures error\n");
        return 1;
    }

    uint8_t* imgBgr = readImage(fileBgr, WINSIZEX, WINSIZEY, BYTECOUNT);
    uint8_t* imgFrt = readImage(fileFrt, WINSIZEX, WINSIZEY, BYTECOUNT, ImageMode::BLENDABLE);
    if (!imgBgr || !imgFrt) {
        printf("image error\n");
        return 1;
    }

    closeImages(&fileBgr, &fileFrt);

    if (WINSIZEX % BOOST_F) {
        printf("BOOST DIVISIBILITY!!!\n");
        return 1;
    }

    Mat image(WINSIZEY, WINSIZEX, CV_8UC4, imgBgr);
    imshow(WINNAME, image);

    clock_t timer = clock();
    double averageFps = 0.;
    long frameCounter = 0;

    int key = 0;
    while (key != 27) {
        blend(image, imgBgr, imgFrt);

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

    free(imgBgr);
    free(imgFrt);

    printf("Program finished 0\n");
    return 0;
}
