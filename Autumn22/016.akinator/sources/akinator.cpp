#include <assert.h>
#include <stdio.h>

#include "include.h"
#include "akinatorIO.h"
#include "akinatorAlgorithms.h"

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

    char input[INPUT_BUFFER_SIZE] = {};
    while (TreeIterator::getRightPtr(&position)) {
        printf("'%s'?\n", *(char const**)TreeIterator::getValue(&position));
        scanf("%s", input);

        if (*input == 'y')
            TreeIterator::right(&position);
        else
            TreeIterator::left(&position);
    }

    printf("Is %s suitable?\n", *(char const**)TreeIterator::getValue(&position));
    scanf("%s", input);

    if (*input == 'y') {
        printf("Enjoy listening.\n");
        return Error::OK;
    }

    char* question = (char*)calloc(INPUT_BUFFER_SIZE, sizeof(char));
    char* name = (char*)calloc(INPUT_BUFFER_SIZE, sizeof(char));
    if (!question || !name)
        return Error::MEM_ERR;

    printf("Sorry to hear. That is all i have. But finally, what is suitable for you?\n");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    scanf(strFParser::parseFCalloc("\n%%%d[^\n]", INPUT_BUFFER_SIZE), name);
#pragma GCC diagnostic pop
    strFParser::freeCalloc();

    Tree::rehangLeft(&akinator->data, &position);
    Tree::addRight(&akinator->data, &position, &name);

    TreeIterator left = position;
    TreeIterator right = position;
    TreeIterator::left(&left);
    TreeIterator::right(&right);

    printf("A kakaya %s v otlichie ot %s?\n",
        *(char const**)TreeIterator::getValue(&right), *(char const**)TreeIterator::getValue(&left));
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    scanf(strFParser::parseFCalloc("\n%%%d[^\n]", INPUT_BUFFER_SIZE), question);
#pragma GCC diagnostic pop
    strFParser::freeCalloc();

    *((char const**)TreeIterator::getValue(&position)) = question;

    return Error::OK;
}

Akinator::Error Akinator::defenition(Akinator* const akinator) {
    char keyword[INPUT_BUFFER_SIZE] = {};

    printf("Print keyword for defenition:\n");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    scanf(strFParser::parseFCalloc("\n%%%d[^\n]", INPUT_BUFFER_SIZE), keyword);
#pragma GCC diagnostic pop
    strFParser::freeCalloc();

    akinatorAlgorithms::FinderResult finderResult = {};
    akinatorAlgorithms::findNode(akinator, keyword, &finderResult);

    if (!finderResult.bestNode.ptr) {
        printf("Sorry, no match\n");
        return Error::OK;
    }
    printf("Matched : %s\n", *(char const**)TreeIterator::getValue(&finderResult.bestNode));

    akinatorAlgorithms::FeatsList* featsList = (akinatorAlgorithms::FeatsList*)calloc(finderResult.depth, sizeof(akinatorAlgorithms::FeatsList));
    if (!featsList)
        return Error::MEM_ERR;

    akinatorAlgorithms::getNodeOrigin(akinator, finderResult.bestNode, finderResult.depth, featsList);

    // printf("Defenition:\n");
    printf("%s is a", *(char const**)TreeIterator::getValue(&finderResult.bestNode));
    for (size_t i = 0; i < finderResult.depth; ++i) {
        if (i > 0)
            printf(",");
        if (!featsList[i].correct)
            printf(" not");
        printf(" %s", featsList[i].feat);
    }
    printf(" song.\n");

    free(featsList);

    return Error::OK;
}
