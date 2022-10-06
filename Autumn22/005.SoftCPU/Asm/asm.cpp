#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "asm.h"

namespace asmbler {
    /**
     * @brief Translate asm text to asm code
     *
     * @param [in] asmText Asm text
     * @param [out] asmCode Asm code
     * @return Error Error code
     */
    Error translate(ListOfLines* asmText, AsmCode* asmCode) {
        assert(asmText != nullptr);
        assert(asmCode != nullptr);
        assert(asmText->size != 0);

        for (int lineI = 0; lineI < asmText->size; ++lineI) {
            //sscanf(asmText->lines[lineI].str, )
        }
        return Error::OK;
    }
}
