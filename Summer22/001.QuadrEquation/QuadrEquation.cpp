#include <stdio.h>
#include <math.h>

#include "compareDouble.h"
#include "QuadrEquation.h"

namespace quadrEquation {
    NumberOfRoots solveLinearEquation(QuadrEquation* equation, double* root1);

    // -----------------------------------------------------------------------

    bool scan(QuadrEquation* equation) {
        assert(equation != nullptr);

        if (scanf("%lg %lg %lg", &equation->a, &equation->b, &equation->c) != 3)
            return false;

        return (
            isfinite(equation->a) &&
            isfinite(equation->b) &&
            isfinite(equation->c));
    }

    void print(QuadrEquation equation) {
        printf("%g*x^2 + %g*x + %g = 0\n", equation.a, equation.b, equation.c);
    }

    NumberOfRoots solveLinearEquation(QuadrEquation* equation, double* root1) {
        assert(equation != nullptr);
        assert(root1 != nullptr);
        if (compareDouble(equation->b, 0.)) {
            // b = 0
            if (compareDouble(equation->c, 0.)) {
                // c = 0
                // 0 = 0
                return NumberOfRoots::INF_ROOTS;
            } else {
                // c != 0
                // 1 = 0
                return NumberOfRoots::NO_ROOTS;
            }
        }
        // b != 0
        // x - 1 = 0
        *root1 = -equation->c / equation->b;
        return NumberOfRoots::ONE_ROOT;
    }

    NumberOfRoots solve(QuadrEquation* equation, double* root1, double* root2) {
        assert(equation != nullptr);
        assert(root1 != nullptr);
        assert(root2 != nullptr);

        if (compareDouble(equation->a, 0.)) {
            // a = 0
            return solveLinearEquation(equation, root1);
        }
        // a != 0

        double discr = (equation->b * equation->b) - (4 * equation->a * equation->c);

        if (discr < 0) {
            // D < 0
            return NumberOfRoots::NO_ROOTS;
        }
        if (compareDouble(discr, 0.)) {
            // D = 0
            *root1 = -equation->b / (2 * equation->a);
            return NumberOfRoots::ONE_ROOT;
        }
        // D > 0

        double discrSqrt = sqrt(discr);
        *root1 = (-equation->b - discrSqrt) / (2 * equation->a);
        *root2 = (-equation->b + discrSqrt) / (2 * equation->a);
        return NumberOfRoots::TWO_ROOTS;
    }
}
