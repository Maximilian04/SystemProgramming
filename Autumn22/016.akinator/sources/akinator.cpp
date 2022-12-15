#include <assert.h>
#include <stdio.h>

#include "akinatorIO.h"

#include "Akinator.h"

/**
 * @brief Akinator constructor
 *
 * @param [out] akinator Akinator
 * @return Akinator::Error Error code
 */
Akinator::Error Akinator::ctor(Akinator* const akinator, DEBUGINFO_CTOR_ARGS_H) {
    assert(akinator);

    DEBUGINFO_CTOR_ARGS_INITIALIZE(akinator);

    Tree__ctorVariableOutFunc(akinator->data, char const*,
    [](ValueOutFunction_t_PARAMS) -> char const* {
        return strFParser::parseFNBuf(bufN, "%s", (char const* const*)valuePtr);
    },
    [](ValueDtorFunction_t_PARAMS) -> int {
        free(*(char**)valuePtr);
        return 0;
    });
    // tree->root = nullptr;

    // tree->elemSize = elemSize;
    // tree->outFunc = outFunc;

    // VERIFY(tree);
    return Error::OK;
}

/**
 * @brief Save akinator data to file
 *
 * @param [in] akinator Akinator
 * @param [in] fileName File name
 * @return Akinator::Error Error code
 */
Akinator::Error Akinator::save(Akinator const* const akinator, char const* const fileName) {
    assert(akinator);
    assert(fileName);

    if (akinatorIO::save(&akinator->data, fileName)) {
        return Error::FILE_ERR;
    }

    return Error::OK;
}

/**
 * @brief Upload akinator data from file
 *
 * @param [out] akinator Akinator
 * @param [in] fileName File name
 * @return Akinator::Error Error code
 */
Akinator::Error Akinator::upload(Akinator* const akinator, char const* const fileName) {
    assert(akinator);
    assert(fileName);



    return Error::OK;
}
