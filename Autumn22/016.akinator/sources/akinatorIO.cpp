#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <sys\stat.h>

#include "akinatorIO.h"

namespace recDescent {
    enum Error {
        OK = 0, ///< No errors
        SYNTAX, ///< Error in file
    };

    enum Dir {
        RIGHT,
        LEFT,
    };

    static void skipSpaces(char const** str);

    static Error getG(char const* s, Tree* tree);
    static Error getNode(char const** str, Tree* tree, TreeIterator* parent, Dir dir = Dir::RIGHT);
    static Error getViscera(char const** str, Tree* tree, TreeIterator* parent, Dir dir);
    static Error getN(char const** str, size_t* value);
}

namespace akinatorIO {
    static _off_t getSizeOfFile(const char* fileName);

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

                fprintf((FILE*)userdata, "%llu:%s\n{", strlen(*(char**)TreeIterator::getValue(iterator)), *(char**)TreeIterator::getValue(iterator));
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

        int fileSize = getSizeOfFile(fileName);
        if (!fileSize) {
            return Error::FILE_ERR;
        }

        FILE* file = fopen(fileName, "rt");
        if (!file) {
            return Error::FILE_ERR;
        }

        char* buffer = (char*)calloc(fileSize + 1, sizeof(char));
        if (!buffer)
            return Error::MEM_ERR;

        size_t freadResult = fread(buffer, sizeof(char), fileSize, file);

        buffer = (char*)realloc((void*)(buffer), sizeof(char) * (freadResult + 1));
        buffer[freadResult] = '\0';

        Error err = Error::OK;
        if (recDescent::getG(buffer, data)) {
            err = Error::FILE_FORMAT_ERR;
        }

        if (fclose(file)) {
            return err ? err : Error::FILE_ERR;
        }
        return err;
    }

    /**
     * @brief Get the size of file
     *
     * @param [in] fileName Name of file
     * @return _off_t Size of file or 0 if error occured
     */
    static _off_t getSizeOfFile(const char* fileName) {
        assert(fileName != nullptr);

        struct stat fileStat = {};

        int statResult = stat(fileName, &fileStat);
        if (statResult != 0)
            return 0;

        assert(statResult == 0 && "Cannot get file info");

        return fileStat.st_size;
    }
}

namespace recDescent {
    static Error getG(char const* s, Tree* tree) {
        assert(s);
        assert(tree);
        assert(Tree::isEmpty(tree));

        char const** str = &s;

        Error err = Error::OK; //getValue(str);

        err = getNode(str, tree, nullptr);
        if (err) {
            printf("Syntax error in symbol '%llu'", str - &s);
            return Error::SYNTAX;
        }

        skipSpaces(str);
        if (**str != '\0') {
            printf("Syntax error : end was not reached");
            return Error::SYNTAX;
        }
        ++(*str);

        return Error::OK;
    }

    static Error getNode(char const** str, Tree* tree, TreeIterator* parent, Dir dir) {
        assert(str);
        assert(*str);
        assert(tree);

        skipSpaces(str);
        if (**str != '{')
            return Error::SYNTAX;
        ++(*str);

        if (**str != '}') {
            Error err = getViscera(str, tree, parent, dir);
            if (err) return err;
        }

        skipSpaces(str);
        if (**str != '}')
            return Error::SYNTAX;
        ++(*str);

        return Error::OK;
    }

    static Error getViscera(char const** str, Tree* tree, TreeIterator* parent, Dir dir) {
        assert(str);
        assert(*str);
        assert(tree);
        assert(!parent || TreeIterator::isValid(parent));


        size_t strLength = 0;
        skipSpaces(str);
        Error err = getN(str, &strLength);
        if (err) return err;


        skipSpaces(str);
        if (**str != ':')
            return Error::SYNTAX;
        ++(*str);


        char* string = (char*)calloc(strLength + 1, sizeof(char));

        skipSpaces(str);
        for (size_t i = 0; i < strLength; ++i) {
            string[i] = **str;
            ++(*str);
        }
        string[strLength] = '\0';

        TreeIterator it{};
        if (parent) {
            TreeIterator::copyTo(parent, &it);

            switch (dir) {
            case Dir::LEFT:
                Tree::addLeft(tree, parent, &string);
                TreeIterator::left(&it);
                break;
            case Dir::RIGHT:
                Tree::addRight(tree, parent, &string);
                TreeIterator::right(&it);
                break;
            default:
                assert(0);
            };
        } else {
            Tree::addRoot(tree, &string);
            Tree::set2Root(tree, &it);
        }


        err = getNode(str, tree, &it, Dir::LEFT);
        if (err) return err;
        err = getNode(str, tree, &it, Dir::RIGHT);
        if (err) return err;

        return Error::OK;
    }

    static Error getN(char const** str, size_t* value) {
        *value = 0;
        bool hasS = false;

        while (
            **str >= '0' &&
            **str <= '9') {

            (*value) = (*value) * 10 + (**str - '0');
            ++(*str);
            hasS = true;
        }

        if (!hasS)
            return Error::SYNTAX;

        return Error::OK;
    }

    static void skipSpaces(char const** str) {
        while (isspace(**str))
            ++(*str);
    }
}
