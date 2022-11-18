#include <logger.h>
#include <graphviz\graphvizTree.h>>

#include "loggerTree.h"

static void logGraphTree(const Tree* const tree);

void logTree(const Tree* const tree) {
    // logger::addBlock();

    // logger__logField(tree, head, p, nullptr);
    // logger__logField(tree, tail, p, nullptr);
    // logger__logField(tree, elemSize, u, 0);

    // logger::logLine("Elements: ");
    // logger::addBlock();

    // if (!Tree::isEmpty(tree)) {
    //     size_t bufN1 = strFParser::addCallocBuf();
    //     size_t bufN2 = strFParser::addCallocBuf();
    //     size_t bufN3 = strFParser::addCallocBuf();

    //     TreeIterator elem;
    //     Tree::begin(tree, &elem);
    //     do {
    //         char const* ptrStr = strFParser::parseFNBuf(bufN1, htmlCyanPointer, TreeIterator::getValue(&elem));
    //         char const* valueStr = tree->outFunc(bufN2, TreeIterator::getValue(&elem));
    //         logger::logLine(strFParser::parseFNBuf(bufN3, "[%s] > %s", ptrStr, valueStr));

    //     } while (!TreeIterator::next(&elem));

    //     strFParser::freeCalloc();
    // }

    // logger::endBlock();

    // logger::endBlock();

    // logGraphTree(tree);
}

#define LOG_GRAPH_FILENAME_TEMPLATE "stuff/log_tree_graph_%d.gv"
#define LOG_GRAPH_IMG_FILENAME_TEMPLATE "stuff/log_tree_graph_%d.png"
#define LOG_FILENAME     strFParser::parseFNBuf(bufN1, LOG_GRAPH_FILENAME_TEMPLATE, logToken)
#define LOG_IMG_FILENAME strFParser::parseFNBuf(bufN2, LOG_GRAPH_IMG_FILENAME_TEMPLATE, logToken)

static void logGraphTree(const Tree* const tree) {
    // static int logToken = 0;
    // ++logToken;
    // size_t bufN  = strFParser::addCallocBuf();
    // size_t bufN1 = strFParser::addCallocBuf();
    // size_t bufN2 = strFParser::addCallocBuf();
    // if (graphviz::openLogFile(LOG_FILENAME)) {
    //     printf("Cannot create graphviz file\n");
    //     return;
    // }

    // graphviz::logGraphHead();

    // if (!Tree::isEmpty(tree)) {
    //     TreeIterator elem;
    //     Tree::begin(tree, &elem);
    //     size_t elemIndex = 0;
    //     do {
    //         graphviz::logElem(elemIndex++, TreeIterator::getElemPtr(&elem), TreeIterator::getNextPtr(&elem), TreeIterator::getPrevPtr(&elem),
    //             Tree::getOutFunc(tree), bufN, TreeIterator::getValue(&elem));
    //     } while (!TreeIterator::next(&elem));

    //     graphviz::logHeadTailEgg(tree->head, tree->tail);
    // }

    // graphviz::logGraphTail();

    // graphviz::closeLogFile();

    // graphviz::run(bufN, LOG_FILENAME, LOG_IMG_FILENAME);
    // logger::logImg(LOG_IMG_FILENAME);

    // strFParser::freeCalloc();
}

#undef LOG_GRAPH_FILENAME_TEMPLATE
#undef LOG_GRAPH_IMG_FILENAME_TEMPLATE
#undef LOG_FILENAME
#undef LOG_IMG_FILENAME
