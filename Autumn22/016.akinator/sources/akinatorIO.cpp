#include <assert.h>

#include "akinatorIO.h"

namespace recDescent {
    double getG(char const* str);
    double getE(char const** str);
    double getT(char const** str);
    double getP(char const** str);
    double getN(char const** str);
}

namespace akinatorIO {
    /**
     * @brief Save data to the file
     *
     * @param [in] data Tree
     * @param [in] fileName File name
     * @return Error Error code
     */
    Error save(Tree const* const data, char const* const fileName) {
        assert(data);
        assert(fileName);

        FILE* file = fopen(fileName, "wt");
        if (!file) {
            return Error::FILE_ERR;
        }

        fprintf(file, "{");
        Tree::dfs(data,
            [](DfsCallbackFunction_t_PARAMS) -> void {
            assert(tree);
            assert(iterator);
            assert(userdata);

            fprintf((FILE*)userdata, "'%s'\n{", (char*)TreeIterator::getValue(iterator));
        },
            [](DfsCallbackFunction_t_PARAMS) -> void {
            assert(tree);
            assert(iterator);
            assert(userdata);

            fprintf((FILE*)userdata, "}\n{");
        },
            [](DfsCallbackFunction_t_PARAMS) -> void {
            assert(tree);
            assert(iterator);
            assert(userdata);

            fprintf((FILE*)userdata, "}\n");
        },
            file
            );
        fprintf(file, "}\n");

        if (fclose(file)) {
            return Error::FILE_ERR;
        }

        return Error::OK;
    }

    /**
     * @brief Upload data to tree from file
     *
     * @param [out] data Tree
     * @param [in] fileName File name
     * @return Error Error code
     */
    Error upload(Tree* const data, char const* const fileName) {
        assert(data);
        assert(fileName);

        if (!Tree::isEmpty(data)) {
            return Error::ISNOT_EMPTY;
        }

        FILE* file = fopen(fileName, "rt");
        if (!file) {
            return Error::FILE_ERR;
        }



        if (fclose(file)) {
            return Error::FILE_ERR;
        }
    }
}

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
