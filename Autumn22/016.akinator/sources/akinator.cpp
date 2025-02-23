#include <assert.h>
#include <stdio.h>

#include "include.h"
#include "akinatorIO.h"
#include "akinatorAlgorithms.h"

#include "texts.h"
#include "voice.h"

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

static bool getAnswer(char* input) {
    scanf("%s", input);

    return *input == 'y';
}

static bool askFeatureQuestion(TreeIterator const* const position, char* input) {
    printf(texts::FEATUREQUESTION, *(char const**)TreeIterator::getValue(position));

    return getAnswer(input);
}

#define SCAN2BUFFER(size, dst) scanf(strFParser::parseFCalloc("\n%%%d[^\n]", size), dst);

Akinator::Error Akinator::guess(Akinator* const akinator) {
    TreeIterator position{};
    if (Tree::set2Root(&akinator->data, &position))
        return Error::EMPTY;

    voice::addText(texts::GUESS_INVITE);
    voice::generate();
    printf(texts::GUESS_INVITE);

    char input[INPUT_BUFFER_SIZE] = {};

    while (TreeIterator::getRightPtr(&position)) {
        if (askFeatureQuestion(&position, input))
            TreeIterator::right(&position);
        else
            TreeIterator::left(&position);
    }

    // voice::addText(strFParser::parseFCalloc(texts::CERTAINQUESTION, *(char const**)TreeIterator::getValue(&position)));
    voice::addText(texts::CERTAINQUESTION);
    voice::generate();
    printf(texts::CERTAINQUESTION, *(char const**)TreeIterator::getValue(&position));

    if (getAnswer(input)) {
        printf(texts::GUESS_GOODBYE);
        return Error::OK;
    }

    char* question = (char*)calloc(INPUT_BUFFER_SIZE, sizeof(char));
    char* name = (char*)calloc(INPUT_BUFFER_SIZE, sizeof(char));
    if (!question || !name)
        return Error::MEM_ERR;

    printf(texts::GUESS_SURRENDER);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    SCAN2BUFFER(INPUT_BUFFER_SIZE, name);
#pragma GCC diagnostic pop
    strFParser::freeCalloc();

    Tree::rehangLeft(&akinator->data, &position);
    Tree::addRight(&akinator->data, &position, &name);

    TreeIterator left = position;
    TreeIterator right = position;
    TreeIterator::left(&left);
    TreeIterator::right(&right);

    printf(texts::GUESS_DIFFQUESTION, *(char const**)TreeIterator::getValue(&right), *(char const**)TreeIterator::getValue(&left));
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    SCAN2BUFFER(INPUT_BUFFER_SIZE, question);
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

Akinator::Error Akinator::difference(Akinator* const akinator) {
    char keyword1[INPUT_BUFFER_SIZE] = {};
    char keyword2[INPUT_BUFFER_SIZE] = {};

    printf("Print two keywords for getting difference:\n");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    scanf(strFParser::parseFCalloc("\n%%%d[^\n]", INPUT_BUFFER_SIZE), keyword1);
    scanf(strFParser::parseFCalloc("\n%%%d[^\n]", INPUT_BUFFER_SIZE), keyword2);
#pragma GCC diagnostic pop
    strFParser::freeCalloc();

    akinatorAlgorithms::FinderResult finderResult1 = {};
    akinatorAlgorithms::FinderResult finderResult2 = {};
    akinatorAlgorithms::findNode(akinator, keyword1, &finderResult1);
    akinatorAlgorithms::findNode(akinator, keyword2, &finderResult2);

    if (!finderResult1.bestNode.ptr) {
        printf("Sorry, no match\n");
        return Error::OK;
    }
    printf("Matched : %s\n", *(char const**)TreeIterator::getValue(&finderResult1.bestNode));
    if (!finderResult2.bestNode.ptr) {
        printf("Sorry, no match\n");
        return Error::OK;
    }
    printf("Matched : %s\n", *(char const**)TreeIterator::getValue(&finderResult2.bestNode));


    akinatorAlgorithms::FeatsList* featsList1 = (akinatorAlgorithms::FeatsList*)calloc(finderResult1.depth, sizeof(akinatorAlgorithms::FeatsList));
    if (!featsList1)
        return Error::MEM_ERR;
    akinatorAlgorithms::FeatsList* featsList2 = (akinatorAlgorithms::FeatsList*)calloc(finderResult2.depth, sizeof(akinatorAlgorithms::FeatsList));
    if (!featsList2)
        return Error::MEM_ERR;

    akinatorAlgorithms::getNodeOrigin(akinator, finderResult1.bestNode, finderResult1.depth, featsList1);
    akinatorAlgorithms::getNodeOrigin(akinator, finderResult2.bestNode, finderResult2.depth, featsList2);

    size_t commonCounter = 0;

    printf("%s and %s are both",
        *(char const**)TreeIterator::getValue(&finderResult1.bestNode),
        *(char const**)TreeIterator::getValue(&finderResult2.bestNode));
    for (size_t i = 0; i < finderResult1.depth && i < finderResult2.depth; ++i) {
        if (featsList1[i].correct != featsList2[i].correct) {
            commonCounter = i;
            break;
        }
        if (i > 0)
            printf(",");
        if (!featsList1[i].correct)
            printf(" not");
        printf(" %s", featsList1[i].feat);
    }
    printf(" songs.\n");

    printf("But %s is",
        *(char const**)TreeIterator::getValue(&finderResult1.bestNode));
    for (size_t i = commonCounter; i < finderResult1.depth; ++i) {
        if (i > commonCounter)
            printf(",");
        if (!featsList1[i].correct)
            printf(" not");
        printf(" %s", featsList1[i].feat);
    }

    printf(" while %s is",
        *(char const**)TreeIterator::getValue(&finderResult2.bestNode));
    for (size_t i = commonCounter; i < finderResult2.depth; ++i) {
        if (i > commonCounter)
            printf(",");
        if (!featsList2[i].correct)
            printf(" not");
        printf(" %s", featsList2[i].feat);
    }
    printf(".\n");

    free(featsList1);
    free(featsList2);

    return Error::OK;
}
