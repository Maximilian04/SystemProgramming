#ifndef QUADREQUATION_H
#define QUADREQUATION_H

#include <cassert>
#include <cerrno>

typedef struct {
    double a;
    double b;
    double c;
} QuadrEquation;

namespace quadrEquation {
    bool scan(QuadrEquation* equation);
    void print(QuadrEquation equation);

    enum NumberOfRoots {
        NO_ROOTS = 0,
        ONE_ROOT = 1,
        TWO_ROOTS = 2,
        INF_ROOTS = 3,
    }; // TODO занести выравнивание в editorconfig

    NumberOfRoots solve(QuadrEquation* equation, double* root1, double* root2);
}

#endif // QUADREQUATION_H
