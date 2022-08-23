#include <stdio.h>
#include <cassert>

#include "quadrEquationIO.h"

/**
 * @brief Ask user to print coefficients for quadratic equation
 * 
 * Is working until gets correct input
 * 
 * @param [out] equationPtr Equation
 */
void inputQuadrEquation(QuadrEquation* equationPtr) {
    printf("Print coefficients for \"a*x^2 + b*x + c = 0\" equation: \n");
    while (!quadrEquation::scan(equationPtr)) {
        while (getchar() != '\n');
        printf("Input is incorrect! Print coefficients for \"a*x^2 + b*x + c = 0\" equation: \n");
    }
}

/**
 * @brief Solves quadratic equation and prints roots
 * 
 * @param [in] equationPtr 
 */
void outputQuadrEquation(QuadrEquation* equationPtr) {
    double root1 = 0;
    double root2 = 0;
    switch (quadrEquation::solve(equationPtr, &root1, &root2)) {
    case quadrEquation::NumberOfRoots::NO_ROOTS:
        printf("No roots\n");
        break;
    case quadrEquation::NumberOfRoots::ONE_ROOT:
        printf("Root: %lg\n", root1);
        break;
    case quadrEquation::NumberOfRoots::TWO_ROOTS:
        printf("Roots: %lg, %lg\n", root1, root2);
        break;
    case quadrEquation::NumberOfRoots::INF_ROOTS:
        printf("Any number is a root\n");
        break;
    default:
        assert(false && "quadrEquation()'s return is not a NumberOfRoots'es member");
    }
}
