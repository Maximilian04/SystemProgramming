#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "loggerList.h"

#include "List.h"

#define VERIFY(obj) if (verify(obj)) { LIST__dump(*obj)); return Error::VERIFIER_ERR; }

/**
 * @brief Push new element to the back of the list
 *
 * @param [out] list List
 * @param [in] size Size of the element
 * @param [in] src Pointer to the new element
 * @return List::Error
 */
List::Error List::pushBack(List* const list, size_t const size, void const* const src) {
    assert(list != nullptr);
    // assert(src != nullptr);

    ListElem* newElem = (ListElem*)calloc(sizeof(ListElem), 1);
    if (!newElem) return Error::MEM_ERR;

    if (list->head) {
        assert(list->head->next == nullptr);

        list->head->next = newElem;
        newElem->prev = list->head;
        list->head = newElem;
    }

    list->head->valuePtr = calloc(size, 1);
    if (!list->head->valuePtr) return Error::MEM_ERR;
    memcpy(list->head->valuePtr, src, size);

    return Error::OK;
}

/**
 * @brief Dump List info
 *
 * @param [in] list List
 * @return List::Error Error code
 */
List::Error List::dump(List* const list, LOGFUNCHEAD_ARGS_H) {
    assert(funcName != nullptr);
    assert(fileName != nullptr);

    Error err = Error::OK;

    logger::openLogFile();

    logger::logHtmlHead();
    logger__logFuncHead());
    if (list == nullptr) {
        logger::emergencyLog("List is nullptr");
        err = Error::NULLPTR_ERR;
    } else {

#ifdef LIST_DEBUG
        logger::logStructHeadDebug("List", list, &list->debugInfo);
#else // !LIST_DEBUG
        logger::logStructHead("List", list);
#endif // LIST_DEBUG

        logList(list);
    }
    logger::logHtmlTail();

    logger::closeLogFile();

    return err;
}
