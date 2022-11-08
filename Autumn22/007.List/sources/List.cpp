#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "loggerList.h"

#include "List.h"

#define VERIFY(obj) if (verify(obj)) { LIST__dump(*obj)); return Error::VERIFIER_ERR; }

/**
 * @brief List constructor
 *
 * @param [out] list List
 * @param [in] elemSize Size of an element
 * @return List::Error Error code
 */
List::Error List::ctor(List* const list, DEBUGINFO_CTOR_ARGS_H, size_t const elemSize) {
    assert(list != nullptr);

    list->debugInfo.objName = objName;
    list->debugInfo.ctorCallLine = ctorCallLine;
    list->debugInfo.ctorCallFile = ctorCallFile;
    list->debugInfo.ctorCallFunc = ctorCallFunc;

    list->elemSize = elemSize;

    // VERIFY(list);
    return Error::OK;
}

/**
 * @brief List destructor
 *
 * @param [out] list List
 * @return List::Error Error code
 */
List::Error List::dtor(List* const list) {
    list->debugInfo.ctorCallLine = -1;

    return Error::OK;
}

/**
 * @brief Push new element to the back of the list
 *
 * @param [out] list List
 * @param [in] src Pointer to the new element
 * @return List::Error
 */
List::Error List::pushBack(List* const list, void const* const src) {
    assert(list != nullptr);

    ListElem* newElem = (ListElem*)calloc(sizeof(ListElem), 1);
    if (!newElem) return Error::MEM_ERR;

    if (list->head) {
        assert(list->head->next == nullptr);

        list->head->next = newElem;
        newElem->prev = list->head;
        list->head = newElem;
    }

    list->head->valuePtr = calloc(list->elemSize, 1);
    if (!list->head->valuePtr) return Error::MEM_ERR;
    if (src)
        memcpy(list->head->valuePtr, src, list->elemSize);
    else
        memset(list->head->valuePtr, 0, list->elemSize);

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

        logger::logStructHeadDebug("List", list, &list->debugInfo);

        logList(list);
    }
    logger::logHtmlTail();

    logger::closeLogFile();

    return err;
}
