/**
 * @file mouse.h
 * @author Maximilian (https://github.com/MaximilianYan)
 * @brief
 * @date 2023-04-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef MOUSE_H
#define MOUSE_H

#include "include.h"

struct MouseInfo {
    int32_t x;
    int32_t y;
    bool flag;
};

void handleMouse(int event, int x, int y, int flags, void* userdata);
bool wasClickCorrect(Mat img, MouseInfo* mouseInfo);

#endif // MOUSE_H
