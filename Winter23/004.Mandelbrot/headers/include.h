/**
 * @file include.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Useful headers
 * @date 2022-12-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef INCLUDE_H
#define INCLUDE_H

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <immintrin.h>

// #pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#include <opencv2/opencv.hpp>
// #include "D:/programming/libraries/opencv-4.6.0/opencv-build-release-freetype/install/include/opencv2/opencv.hpp"
// #pragma GCC diagnostic pop

using namespace cv;
using namespace std;

const int16_t WINSIZEX = 1000;
const int16_t WINSIZEY = 704;

float SCALE = 1.f / 400.0f; // [1/px]
float OFFSETX = -2.f;
float OFFSETY = -SCALE * WINSIZEY / 2.f;

const float INFRAD = 10.f;
const int16_t INFNUM = 700;

#endif // INCLUDE_H
