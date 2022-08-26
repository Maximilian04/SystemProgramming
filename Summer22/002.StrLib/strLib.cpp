#include <assert.h>

#include "strLib.h"

namespace strLib {
    /**
     * @brief Calculate lenght of string
     *
     * @param [in] str string
     * @return int Lenght without \0
     */
    int strlen(const char* str) {
        assert(str != nullptr);

        int lenght = 0;
        for (lenght = 0; str[lenght] != '\0'; ++lenght);

        return lenght;
    }

    /**
     * @brief Copyes **count** characters from **src** to **dest**
     *
     * @param [out] dst Pointer to the character array to copy to
     * @param [in] src Pointer to the character array to copy from
     * @param [in] count Maximum number of characters to copy
     * @return char* Returns a copy of dest
     */
    char* strncpy(char* dst, const char* src, int count) {
        assert(dst != nullptr);
        assert(src != nullptr);

        int length = 0;
        for (length = 0; src[length] != '\0' && length < count; ++length) {
            dst[length] = src[length];
        }

        for (; length < count; ++length) {
            dst[length] = '\0';
        }

        return dst;
    }

    /**
     * @brief Adds **count** characters from **src** to end of **dest**
     *
     * @param [out] dst Pointer to the character array to copy to
     * @param [in] src Pointer to the character array to copy from
     * @param [in] count Maximum number of characters to copy
     * @return char* Returns a copy of dest
     */
    char* strncat(char* dst, const char* src, int count) {
        assert(dst != nullptr);
        assert(src != nullptr);

        int dstLength = 0;
        int srcLength = 0;
        for (dstLength = 0, srcLength = 0; dst[dstLength] != '\0'; ++dstLength);

        for (; src[srcLength] != '\0' && srcLength < count; ++dstLength, ++srcLength) {
            dst[dstLength] = src[srcLength];
        }

        dst[dstLength] = '\0';

        return dst;
    }

    /**
     * @brief Find first occurrence **needle** string in **haystack** string
     *
     * @param [in] haystack Pointer to the character array to copy to
     * @param [in] needle Pointer to the character array to copy from
     * @return const char* Begin of occurring or nullptr in the case of absence
     */
    const char* strstr(const char* haystack, const char* needle) {
        assert(haystack != nullptr);
        assert(needle != nullptr);

        int haystackBase = 0;
        for (haystackBase = 0; haystack[haystackBase] != '\0'; ++haystackBase) {
            for (int needleI = 0; haystack[haystackBase + needleI] == needle[needleI] || needle[needleI] == '\0'; ++needleI) {
                if (needle[needleI] == '\0') {
                    return haystack + haystackBase;
                }
            }
        }

        return nullptr;
    }

    /**
     * @brief Finds the next token in a string **str**
     *
     * @param [out] str String to tokenize
     * @param [in] delim String identifying delimiters
     * @return char*
     */
    char* strtok(char* str, const char* delim) {
        assert(delim != nullptr);
        static char* staticPointer = nullptr;

        if (str == nullptr) {
            str = staticPointer;
        }
        assert(str != nullptr);

        int strI = 0;
        char* tokenBegin = nullptr;

        for (strI = 0; str[strI] != '\0'; ++strI) {
            if (!tokenBegin) { // don't hasContainedChar
                bool isContained = false;
                for (int delimI = 0; delim[delimI] != '\0'; ++delimI) {
                    if (str[strI] == delim[delimI]) {
                        isContained = true;
                        break;
                    }
                }

                if (!isContained) {
                    tokenBegin = str + strI;
                }

            } else { // hasContainedChar
                bool isContained = false;
                for (int delimI = 0; delim[delimI] != '\0'; ++delimI) {
                    if (str[strI] == delim[delimI]) {
                        isContained = true;
                        break;
                    }
                }

                if (isContained) {
                    str[strI] = '\0';
                    staticPointer = str + strI + 1;
                }
            }
        }

        return tokenBegin;
    }

}
