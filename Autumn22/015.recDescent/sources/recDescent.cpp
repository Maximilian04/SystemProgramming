#include <assert.h>

#include "recDescent.h"

// #include <stdio.h>

namespace recDescent {
    double getG(char const* s) {
        // printf("G");
        char const** str = &s;

        double value = 0;

        value = getE(str);

        assert(**str == '\0' && "syntax error");
        ++(*str);

        return value;
    }

    double getE(char const** str) {
        // printf("E");
        double value = 0;

        value = getT(str);

        while (
            **str == '+' ||
            **str == '-') {

            bool isPositive = **str == '+';
            ++(*str);

            if (isPositive) {
                value += getT(str);
            } else {
                value -= getT(str);
            }
        }

        return value;
    }

    double getT(char const** str) {
        // printf("T");
        double value = 0;

        value = getP(str);

        while (
            **str == '*' ||
            **str == '/') {

            bool multiply = **str == '*';
            ++(*str);

            if (multiply) {
                value *= getP(str);
            } else {
                value /= getP(str);
            }
        }

        return value;
    }

    double getP(char const** str) {
        // printf("P");
        double value = 0;

        if (**str == '(') {
            ++(*str);
            value = getE(str);
            ++(*str);
        } else {
            value = getN(str);
        }

        return value;
    }

    double getN(char const** str) {
        // printf("N");
        double value = 0;
        bool hasS = false;

        while (
            **str >= '0' &&
            **str <= '9') {

            value = value * 10 + (**str - '0');
            ++(*str);
            hasS = true;
        }

        assert(hasS && "syntax error");

        return value;
    }
}
