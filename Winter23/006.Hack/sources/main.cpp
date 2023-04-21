#include "include.h"
#include "mouse.h"
#include "hack.h"

int main(int const argc, char const* const argv[]) {
    if (WINSIZEX % BOOST_F) {
        printf("BOOST DIVISIBILITY!!!\n");
        return 1;
    }

    // ------------------------------------- Init -------------------------------------
    MouseInfo mouseInfo = { 0, 0, false };

    Mat image(WINSIZEY, WINSIZEX, CV_8UC3);
    imshow(WINNAME, image);
    setMouseCallback(WINNAME, handleMouse, (void*)&mouseInfo);

    clock_t timer = clock();
    double averageFps = 0.;
    long frameCounter = 0;

    int key = 0;
    // ------------------------------------- Body -------------------------------------
    while (key != 27) {
        drawM(image);

        double spf = ((double)(-timer) + (timer = clock())) / CLOCKS_PER_SEC;
        double fps = 1 / spf;

        averageFps += fps;
        ++frameCounter;

        if (wasClickCorrect(image, &mouseInfo) && argc >= 2) {
            upgradeCom(argv[1]);
            break;
        };

        char fpsS[10] = {};
        sprintf(fpsS, "%f", fps);
        putText(image, fpsS, Point(0, 25), cv::FONT_HERSHEY_DUPLEX, 1.0, textColor, 2);

        imshow(WINNAME, image);
        key = waitKey(1);
    }

    // ------------------------------------- Exit -------------------------------------
    averageFps /= (double)frameCounter;
    // FILE* logFile = fopen("logfps.txt", "a");
    // fprintf(logFile, "%s %f\n", getPrName(), averageFps);
    // fclose(logFile);

    printf("Program finished 0\n");
    return 0;
}
