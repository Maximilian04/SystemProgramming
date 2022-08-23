#pragma once

typedef struct {
    double a;
    double b;
    double c;
} QuadrEquation;

namespace quadrEquation {
    void scan(QuadrEquation* equation);
    void print(QuadrEquation equation);

    enum NumberOfRoots {
        NO_ROOTS = 0,
        ONE_ROOT,
        TWO_ROOTS,
        INF_ROOTS,
    };

    NumberOfRoots solve(QuadrEquation* equation, double* root1, double* root2);
}
