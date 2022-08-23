#include "quadrEquationIO.h"

int main() {
    QuadrEquation equation = {};

    inputQuadrEquation(&equation);
    quadrEquation::print(equation);
    outputQuadrEquation(&equation);

    return 0;
}
