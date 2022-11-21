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
 * @param [in] outFunc Pointer to a function for printing elements'es value
 * @return List::Error Error code
 */
List::Error List::ctor(List* const list, DEBUGINFO_CTOR_ARGS_H, size_t const elemSize, ValueOutFunction_t outFunc) {
    assert(list);

    DEBUGINFO_CTOR_ARGS_INITIALIZE(list);

    list->head = nullptr;
    list->tail = nullptr;

    list->elemSize = elemSize;
    list->outFunc = outFunc;

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
    assert(list);

    while (!List::isEmpty(list)) {
        popBack(list);
    }

    list->debugInfo.objName = "ZZZOMBIE";

    return Error::OK;
}

#define MAKE_NEW_ELEMENT                                             \
    ListElem* const newElem = (ListElem*)calloc(sizeof(ListElem), 1); \
    if (!newElem) return Error::MEM_ERR;

#define SET_NEW_ELEMENT_VALUE                       \
    newElem->valuePtr = calloc(list->elemSize, 1);   \
    if (!newElem->valuePtr) return Error::MEM_ERR;    \
    if (src)                                           \
        memcpy(newElem->valuePtr, src, list->elemSize); \
    else                                                 \
        memset(newElem->valuePtr, 0, list->elemSize);

/**
 * @brief Push new element to the back of the list
 *
 * @param [out] list List
 * @param [in] src Pointer to the new element value
 * @return List::Error Error code
 */
List::Error List::pushBack(List* const list, void const* const src) { //TODO переписать, там в дальнейших ошибочки могут быть
    assert(list);

    MAKE_NEW_ELEMENT;

    if (list->head) {
        assert(list->tail);
        assert(list->head->next == nullptr);

        list->head->next = newElem;
        newElem->prev = list->head;
    } else {
        assert(!list->tail);
        list->tail = newElem;
    }
    list->head = newElem;

    SET_NEW_ELEMENT_VALUE;

    return Error::OK;
}

/**
 * @brief Push new element to the front of the list
 *
 * @param [out] list List
 * @param [in] src Pointer to the new element value
 * @return List::Error Error code
 */
List::Error List::pushFront(List* const list, void const* const src) {
    assert(list);

    MAKE_NEW_ELEMENT;

    if (list->tail) {
        assert(list->head);
        assert(list->tail->prev == nullptr);

        list->tail->prev = newElem;
        newElem->next = list->tail;
    } else {
        assert(!list->head);
        list->head = newElem;
    }
    list->tail = newElem;

    SET_NEW_ELEMENT_VALUE;

    return Error::OK;
}

/**
 * @brief Pop an element from the back of the list
 *
 * @param [out] list List
 * @return List::Error Error code
 */
List::Error List::popBack(List* const list) {
    assert(list);

    if (!list->head) {
        assert(!list->tail);
        return Error::EMPTY;
    }
    assert(list->tail);

    assert(!list->head->next);
    ListElem* elem = list->head;

    free(elem->valuePtr);
    elem->valuePtr = nullptr;

    if (elem->prev) {
        list->head = elem->prev;
        list->head->next = nullptr;
    } else {
        assert(list->head == list->tail);
        list->head = nullptr;
        list->tail = nullptr;
    }
    free(elem);

    return Error::OK;
}

/**
 * @brief Pop an element from the front of the list
 *
 * @param [out] list List
 * @return List::Error Error code
 */
List::Error List::popFront(List* const list) {
    assert(list);

    if (!list->head) {
        assert(!list->tail);
        return Error::EMPTY;
    }
    assert(list->tail);

    assert(!list->tail->prev);
    ListElem* elem = list->tail;

    free(elem->valuePtr);
    elem->valuePtr = nullptr;

    if (elem->next) {
        list->tail = elem->next;
        list->tail->prev = nullptr;
    } else {
        assert(list->head == list->tail);
        list->head = nullptr;
        list->tail = nullptr;
    }
    free(elem);

    return Error::OK;
}

#define IT (iterator->ptr)

/**
 * @brief Add new element after the element of list
 *
 * @param [out] list List
 * @param [in] iterator Iterator to the element
 * @param [in] src Pointer to the new element value
 * @return List::Error Error code
 */
List::Error List::insertAfter(List* const list, ListIterator const* const iterator, void const* const src) {
    assert(list);
    assert(iterator);

    Error err = OK;
    if (IT->next == nullptr) {
        err = pushBack(list, src);
        return err;
    }

    MAKE_NEW_ELEMENT;

    assert(IT->next->prev == IT);

    newElem->prev = IT;
    newElem->next = IT->next;

    IT->next->prev = newElem;
    IT->next = newElem;

    SET_NEW_ELEMENT_VALUE;

    return Error::OK;
}

/**
 * @brief Add new element before the element of list
 *
 * @param [out] list List
 * @param [in] iterator Iterator to the element
 * @param [in] src Pointer to the new element value
 * @return List::Error Error code
 */
List::Error List::insertBefore(List* const list, ListIterator const* const iterator, void const* const src) {
    assert(list);
    assert(iterator);

    Error err = OK;
    if (IT->prev == nullptr) {
        err = pushFront(list, src);
        return err;
    }

    MAKE_NEW_ELEMENT;


    assert(IT->prev->next == IT);

    newElem->next = IT;
    newElem->prev = IT->prev;

    IT->prev->next = newElem;
    IT->prev = newElem;

    SET_NEW_ELEMENT_VALUE;

    return Error::OK;
}

/**
 * @brief Add new element to the list
 *
 * @param [out] list List
 * @param [in] iterator Iterator to the element
 * @param [in] direction Does need insert BEFORE or AFTER the element
 * @param [in] src Pointer to the new element value
 * @return List::Error Error code
 */
List::Error List::insert(List* const list, ListIterator const* const iterator, Direction direction, void const* const src) {
    switch (direction) {
    case Direction::FORWARD:
        return insertAfter(list, iterator, src);
    case Direction::BACKWARD:
        return insertBefore(list, iterator, src);
    default:
        assert(0);
    }

    return Error::OK;
}


/**
 * @brief Erase element from the list
 *
 * @param [out] list List
 * @param [out] iterator Iterator to the element
 * @param [in] direction If iterator will be set to the next or previous element (**nullptr** if there is no such an element)
 * @return List::Error Error code
 */
List::Error List::erase(List* const list, ListIterator* const iterator, Direction direction) {
    assert(list);
    assert(iterator);

    Error err = OK;
    if (IT->next == nullptr) {
        err = popBack(list);

        switch (direction) {
        case Direction::FORWARD:
            IT = nullptr;
            break;
        case Direction::BACKWARD:
            List::rbegin(list, iterator);
            break;
        default:
            assert(0);
        }

        return err;
    }
    if (IT->prev == nullptr) {
        err = popFront(list);
        IT = nullptr;

        switch (direction) {
        case Direction::FORWARD:
            List::begin(list, iterator);
            break;
        case Direction::BACKWARD:
            IT = nullptr;
            break;
        default:
            assert(0);
        }

        return err;
    }


    assert(IT->prev->next == IT);
    assert(IT->next->prev == IT);
    IT->prev->next = IT->next;
    IT->next->prev = IT->prev;

    ListElem* elemToSet;
    switch (direction) {
    case Direction::FORWARD:
        elemToSet = IT->next;
        break;
    case Direction::BACKWARD:
        elemToSet = IT->prev;
        break;
    default:
        assert(0);
    }

    free(IT->valuePtr);
    IT->valuePtr = nullptr;
    free(IT);

    IT = elemToSet;

    return Error::OK;
}

#undef MAKE_NEW_ELEMENT
#undef SET_NEW_ELEMENT_VALUE

/**
 * @brief Is list empty
 *
 * @param [in] list List
 */
bool List::isEmpty(List const* const list) {
    assert(list);
    return !list->head;
}

/**
 * @brief Get the first element of the list
 *
 * @param [in] list List
 * @param [out] iterator Iterator to the first element
 * @return Error Error code
 */
List::Error List::begin(List const* const list, ListIterator* const iterator) {
    assert(list);
    assert(iterator);

    IT = list->tail;

    return Error::OK;
}

/**
 * @brief Get the last element of the list
 *
 * @param [in] list List
 * @param [out] iterator Iterator to the last element
 * @return Error Error code
 */
List::Error List::rbegin(List const* const list, ListIterator* const iterator) {
    assert(list);
    assert(iterator);

    IT = list->head;

    return Error::OK;
}

/**
 * @brief Set iterator to element with logic **index**
 * 
 * @param [in] list List
 * @param [out] iterator Iterator for writing to
 * @param [in] index Wanted index
 * @return List::Error Error code
 */
List::Error List::set2index(List const* const list, ListIterator* const iterator, size_t const index) {
    assert(list);
    assert(iterator);

    logger::logMsg(COLORED_TEXT(COLORS_SETTINGS_CRINGE_TEXTCOLOR, "Чел, ты................................."));

    List::begin(list, iterator);
    size_t counter = 0;
    while (counter < index && !ListIterator::next(iterator)) {
        counter++;
    }

    if (counter != index) {
        IT = nullptr;
        return Error::OUT_OF_SIZE;
    }

    return Error::OK;
}

#undef IT

/**
 * @brief Get list's outFunc
 *
 * @param [in] list List
 * @return ValueOutFunction_t outFunc
 */
ValueOutFunction_t List::getOutFunc(List const* const list) {
    assert(list);

    return list->outFunc;
}

/**
 * @brief Dump List info
 *
 * @param [in] list List
 * @return List::Error Error code
 */
List::Error List::dump(List* const list, LOGFUNCHEAD_ARGS_H) {
    assert(funcName);
    assert(fileName);

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
