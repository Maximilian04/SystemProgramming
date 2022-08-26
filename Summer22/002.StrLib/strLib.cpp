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
}
