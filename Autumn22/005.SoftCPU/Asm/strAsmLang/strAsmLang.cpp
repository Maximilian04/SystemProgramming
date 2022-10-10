#include <string.h>
#include <assert.h>

#include "strAsmLang.h"

namespace strAsmLang {
    /**
     * @brief Parse commandName from line
     *
     * @param [in] line Line
     * @param [out] buffer Buffer for commandName
     * @param [out] length Got commanName's length (excluding \0)
     * @param [in] maxLength Max size of buffer
     * @return Error Error code
     */
    Error getCommandName(const Line* line, char* buffer, int* length, int maxLength) {
        assert(line != nullptr);
        assert(buffer != nullptr);
        assert(length != nullptr);

        int index = 0;
        do {
            if (index >= maxLength)
                return Error::BUF_OVERFLOW;
            if (index > line->lenght)
                return Error::BROKEN_LINE;

            buffer[index] = line->str[index];

            if (buffer[index] == '@')
                buffer[index] = '\0';
            
            if (buffer[index] == '\0')
                break;
        } while (++index);

        *length = index;

        return Error::OK;
    }
}