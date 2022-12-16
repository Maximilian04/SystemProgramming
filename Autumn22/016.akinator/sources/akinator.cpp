#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "include.h"
#include "akinatorIO.h"

#include "Akinator.h"

static double getScore(char const* keyword, const TreeIterator* it);

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

Akinator::Error Akinator::findNode(Akinator* const akinator, char const* keyword, FinderResult* result) {
    struct SearchInfo {
        char const* keyword;
        double bestScore;
        TreeIterator bestNode;
        size_t depth;
        size_t bestNodeDepth;
    };

    SearchInfo searchInfo{ keyword, 0.0, {}, 0, 0 };

    if (Tree::dfs(&akinator->data,
        [](DfsCallbackFunction_t_PARAMS) -> void {
            assert(tree);
            assert(iterator);
            assert(userdata);

            double score = getScore(((SearchInfo*)userdata)->keyword, iterator);
            if (score > ((SearchInfo*)userdata)->bestScore) {
                ((SearchInfo*)userdata)->bestScore = score;
                ((SearchInfo*)userdata)->bestNode = *iterator;
                ((SearchInfo*)userdata)->bestNodeDepth = ((SearchInfo*)userdata)->depth;
            }

            ++(((SearchInfo*)userdata)->depth);
        },
        nullptr, 
        [](DfsCallbackFunction_t_PARAMS) -> void {
            assert(tree);
            assert(iterator);
            assert(userdata);

            --(((SearchInfo*)userdata)->depth);
        }, &searchInfo)) {
            return Error::FINDER_ERR;
        }

    result->bestNode = searchInfo.bestNode;
    result->depth = searchInfo.bestNodeDepth;

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

/**
 * @brief Calc score of the node
 *
 * @param [in] keyword Keyword
 * @param [in] it Iterator
 * @return double Score
 */
static double getScore(char const* keyword, const TreeIterator* it) {
    double bestScore = 0;
    char const* name = *(char const**)(TreeIterator::getValue(it));
    size_t keyLen = strlen(keyword);
    size_t nameLen = strlen(name);

    if (nameLen < keyLen)
        return 0.0;

    for (size_t shift = 0; shift <= (nameLen - keyLen); ++shift) {
        double score = 0;
        for (size_t i = 0; i < keyLen; ++i) {
            score += (keyword[i] == name[i + shift]);
        }
        if (score > bestScore)
            bestScore = score;
    }

    return bestScore;
}

Akinator::Error Akinator::defenition(Akinator* const akinator) {
    char keyword[INPUT_BUFFER_SIZE] = {};

    printf("Print keyword for defenition:\n");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    scanf(strFParser::parseFCalloc("\n%%%d[^\n]", INPUT_BUFFER_SIZE), keyword);
#pragma GCC diagnostic pop
    strFParser::freeCalloc();

    FinderResult finderResult = {};
    findNode(akinator, keyword, &finderResult);    

    if (!finderResult.bestNode.ptr) {
        printf("Sorry, no match\n");
        return Error::OK;
    }
    printf("Matched : %s\n", *(char const**)TreeIterator::getValue(&finderResult.bestNode));

    struct DefList { 
        char const* feat;
        bool correct;
    };
    struct DefInfo {
        TreeIterator bestNode;
        DefList* defList;
        size_t depth;
    };

    DefInfo defInfo{ finderResult.bestNode, nullptr, 0 };
    defInfo.defList = (DefList*)calloc(finderResult.depth, sizeof(DefList));
    if (!defInfo.defList)
        return Error::MEM_ERR;

    Tree::dfs(&akinator->data,
        [](DfsCallbackFunction_t_PARAMS) -> void {
            assert(tree);
            assert(iterator);
            assert(userdata);

            if (((DefInfo*)userdata)->bestNode.ptr == iterator->ptr)
                ((DefInfo*)userdata)->bestNode.ptr = nullptr;
            if (((DefInfo*)userdata)->bestNode.ptr == nullptr)
                return;
            // printf("%d\n", ((DefInfo*)userdata)->depth);

            (((DefInfo*)userdata)->defList)[((DefInfo*)userdata)->depth].feat = *(char const**)TreeIterator::getValue(iterator);
            (((DefInfo*)userdata)->defList)[((DefInfo*)userdata)->depth].correct = false;

            ++(((DefInfo*)userdata)->depth);
        },
        [](DfsCallbackFunction_t_PARAMS) -> void {
            assert(tree);
            assert(iterator);
            assert(userdata);

            if (((DefInfo*)userdata)->bestNode.ptr == nullptr)
                return;

            (((DefInfo*)userdata)->defList)[((DefInfo*)userdata)->depth - 1].correct = true;
        },
        [](DfsCallbackFunction_t_PARAMS) -> void {
            assert(tree);
            assert(iterator);
            assert(userdata);

            --(((DefInfo*)userdata)->depth);
        }, &defInfo);

    // printf("Defenition:\n");
    printf("%s is a", *(char const**)TreeIterator::getValue(&finderResult.bestNode));
    for (size_t i = 0; i < finderResult.depth; ++i) {
        if (i > 0)
            printf(",");
        if (!defInfo.defList[i].correct)
            printf(" not");
        printf(" %s", defInfo.defList[i].feat);
    }
    printf(" song.\n");

    return Error::OK;
}
