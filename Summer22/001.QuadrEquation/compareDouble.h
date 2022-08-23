#ifndef COMPAREDOUBLE_H
#define COMPAREDOUBLE_H

#include <cmath>

#define DOUBLE_COMPARE_ACC (1e-10)

inline bool compareDouble(double a, double b) {
    return (abs(a - b) < DOUBLE_COMPARE_ACC);
}

#endif // COMPAREDOUBLE_H
