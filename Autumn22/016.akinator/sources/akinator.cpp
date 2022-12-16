#include <assert.h>
#include <stdio.h>

#include "include.h"
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

    Tree__ctor(akinator->data, char const*, "%s",
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
 * @brief Akinator constructor
 *
 * @param [out] akinator Akinator
 * @return Akinator::Error Error code
 */
Akinator::Error Akinator::dtor(Akinator* const akinator) {
    assert(akinator);

    Tree::dtor(&akinator->data);

    akinator->debugInfo.objName = "ZZZOMBIE";

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

    switch (akinatorIO::upload(&akinator->data, fileName)) {
    case akinatorIO::Error::FILE_ERR:
        return Error::FILE_ERR;
        break;
    case akinatorIO::Error::FILE_FORMAT_ERR:
        return Error::FILE_FORMAT_ERR;
        break;
    case akinatorIO::Error::ISNOT_EMPTY:
        return Error::UPLOAD_TO_NOT_EMPTY;
        break;
    case akinatorIO::Error::MEM_ERR:
        return Error::MEM_ERR;
        break;
    case akinatorIO::Error::OK:
        break;
    default:
        assert(false);
    }

    return Error::OK;
}

Akinator::Error Akinator::guess(Akinator* const akinator) {
    TreeIterator position{};
    if (Tree::set2Root(&akinator->data, &position))
        return Error::EMPTY;

    char input[INPUT_BUFFER_SIZE];
    while (TreeIterator::getRightPtr(&position)) {
        printf("%s\n", *(char const**)TreeIterator::getValue(&position));
        scanf("%s", input);

        if (*input == 'y')
            TreeIterator::right(&position);
        else
            TreeIterator::left(&position);
    }

    printf("Is it %s?\n", *(char const**)TreeIterator::getValue(&position));
    scanf("%s", input);

    if (*input == 'y')
        printf("Yeeee\n");
    else
        printf("Nooo0o\n");

    return Error::OK;
}
