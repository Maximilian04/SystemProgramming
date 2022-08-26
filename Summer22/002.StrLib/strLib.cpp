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
     * @brief Copyes **count** symbols from **src** to **dest**
     *
     * @param [out] dest Pointer to the character array to copy to
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
}
