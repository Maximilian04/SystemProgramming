/**
 * @file compareDouble.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Comparing double variables
 * @date 2022-08-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef COMPAREDOUBLE_H
#define COMPAREDOUBLE_H

#include <cmath>

/**
 * @brief Accuracy of comparing double variables
 * 
 */
#define DOUBLE_COMPARE_ACC (1e-10)

/**
 * @brief Compares two double variables
 *
 * Compares two double variables with **DOUBLE_COMPARE_ACC** accuracy
 *   
 * @return true if two variables are equal
 */
inline bool compareDouble(double a, double b) {
    return (fabs(a - b) < DOUBLE_COMPARE_ACC);
}

#endif // COMPAREDOUBLE_H
