#include <assert.h>
#include <stdlib.h>

#include "AsmCode.h"

namespace asmCode {
    /**
     * @brief Calloc buffer of asmLang::MAX_CODE_SIZE size for asmCode object
     *
     * @param [out] asmCode asmCode object
     * @return int 0 if no error occures
     */
    int createBuf(AsmCode* asmCode) {
        return createBuf(asmCode, asmLang::MAX_CODE_SIZE);
    }

    /**
     * @brief Calloc buffer for asmCode object
     *
     * @param [out] asmCode asmCode object
     * @param [in] size Size of buffer
     * @return int 0 if no error occures
     */
    int createBuf(AsmCode* asmCode, size_t size) {
        assert(asmCode != nullptr);
        assert(asmCode->code == nullptr);

        asmCode->code = (AsmCode_t*)calloc(size, sizeof(AsmCode_t));
        assert(asmCode->code != nullptr);
        asmCode->codeBufferSize = size;

        return 0;
    }


    int freeBuf(AsmCode* asmCode) {
        assert(asmCode != nullptr);
        assert(asmCode->code != nullptr);

        free(asmCode->code);
        asmCode->code = nullptr;
        asmCode->pc = 0;

        return 0;
    }

    /**
     * @brief Add command to machine code
     *
     * @param [out] asmCode AsmCode object
     * @param [in] byte Command to add
     */
    void add(AsmCode* asmCode, AsmCode_t byte) {
        assert(asmCode != nullptr);
        assert(asmCode->code != nullptr);
        // assert(asmCode->pc >= 0);

        asmCode->code[asmCode->pc] = byte;
        asmCode->pc++;
    }

    /**
     * @brief Get pointer to the last machine code memory field
     *
     * @param [in] asmCode AsmCode object
     * @return AsmCode_t* Pointer
     */
    AsmCode_t* getCodePtr(AsmCode* asmCode) {
        assert(asmCode != nullptr);
        assert(asmCode->code != nullptr);
        assert(asmCode->pc > 0);

        return &asmCode->code[asmCode->pc - 1];
    }
}
