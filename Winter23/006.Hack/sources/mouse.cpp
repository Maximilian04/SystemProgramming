#include "mouse.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void handleMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDBLCLK) {
        MouseInfo* mouseInfo = (MouseInfo*)userdata;

        mouseInfo->flag = true;
        mouseInfo->x = x;
        mouseInfo->y = y;
    }
}
#pragma GCC diagnostic pop

bool wasClickCorrect(Mat img, MouseInfo* mouseInfo) {
    if (!mouseInfo->flag) return false;

    mouseInfo->flag = false;
    return img.at<Vec3b>(mouseInfo->y, mouseInfo->x) == Vec3b(0, 0, 0);
}
