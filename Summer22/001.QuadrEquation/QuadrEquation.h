/**
 * @file QuadrEquation.h
 * @author Maximilian (https://github.com/Maximilian04)
 * @brief Quadratic equation description and solution
 * @date 2022-08-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef QUADREQUATION_H
#define QUADREQUATION_H

#include <cassert>
#include <cerrno>

 /**
  * @brief Coefficients for quadratic equation
  *
  * Equation like \f a*x^2 + b*x + x = 0 \f
  */
typedef struct {
    /// coefficient before x^2
    double a;
    /// coefficient before x^1
    double b;
    /// coefficient before x^0
    double c;
} QuadrEquation;

namespace quadrEquation {
    bool scan(QuadrEquation* equation);
    void print(QuadrEquation equation);

    enum NumberOfRoots {
        NO_ROOTS = 0,
        ONE_ROOT,
        TWO_ROOTS,
        INF_ROOTS,
    }; // TODO занести выравнивание в editorconfig

    NumberOfRoots solve(QuadrEquation* equation, double* root1, double* root2);
}

#endif // QUADREQUATION_H
