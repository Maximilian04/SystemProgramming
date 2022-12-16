#include <assert.h>
#include <string.h>

#include "akinatorAlgorithms.h"

namespace akinatorAlgorithms {
    static double getScore(char const* keyword, const TreeIterator* it);

    Akinator::Error findNode(Akinator* const akinator, char const* keyword, FinderResult* result) {
        assert(akinator);
        assert(keyword);
        assert(result);

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
                return Akinator::Error::FINDER_ERR;
            }

        result->bestNode = searchInfo.bestNode;
        result->depth = searchInfo.bestNodeDepth;

        return Akinator::Error::OK;
    }

    Akinator::Error getNodeOrigin(Akinator* const akinator, TreeIterator node, size_t maxDepth, FeatsList* result) {
        assert(akinator);
        assert(node.ptr);
        assert(result);

        struct DefInfo {
            TreeIterator bestNode;
            size_t maxDepth;
            FeatsList* featsList;
            size_t depth;
        };

        DefInfo defInfo{ node, maxDepth, result, 0 };

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

                if (((DefInfo*)userdata)->depth < ((DefInfo*)userdata)->maxDepth) {
                    (((DefInfo*)userdata)->featsList)[((DefInfo*)userdata)->depth].feat = *(char const**)TreeIterator::getValue(iterator);
                    (((DefInfo*)userdata)->featsList)[((DefInfo*)userdata)->depth].correct = false;
                }

                ++(((DefInfo*)userdata)->depth);
            },
            [](DfsCallbackFunction_t_PARAMS) -> void {
                assert(tree);
                assert(iterator);
                assert(userdata);

                if (((DefInfo*)userdata)->bestNode.ptr == nullptr)
                    return;

                (((DefInfo*)userdata)->featsList)[((DefInfo*)userdata)->depth - 1].correct = true;
            },
            [](DfsCallbackFunction_t_PARAMS) -> void {
                assert(tree);
                assert(iterator);
                assert(userdata);

                --(((DefInfo*)userdata)->depth);
            }, &defInfo);

        return Akinator::Error::OK;
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
}
