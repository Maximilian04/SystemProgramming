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
List::Error List::ctor(List* const list, DEBUGINFO_CTOR_ARGS_H, size_t const elemSize, ValueOutFunction_t outFunc, size_t capacity) {
    assert(list);

    DEBUGINFO_CTOR_ARGS_INITIALIZE(list);

    list->freeTail = 0;
    list->size = 0;
    list->capacity = 0;

    list->elemSize = elemSize;
    list->outFunc = outFunc;

    list->bufferElem = (ListElem*)calloc(1, sizeof(ListElem));
    list->bufferValue = calloc(1, list->elemSize);
    if (!list->bufferElem) return Error::MEM_ERR;
    if (!list->bufferValue) return Error::MEM_ERR;

    resize(list, capacity);

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

    list->freeTail = 0;
    list->size = 0;
    list->capacity = 0;

    /*while (!List::isEmpty(list)) {
        popBack(list);
    }*/
    free(list->bufferElem);
    free(list->bufferValue);

    list->bufferElem = nullptr;
    list->bufferValue = nullptr;

    list->debugInfo.objName = "ZZZOMBIE";

    return Error::OK;
}

/**
 * @brief Linearise (& resize) buffer
 *
 * @param [out] list
 * @param [in] newCapacity New capacity
 * @return List::Error Error code
 */
List::Error List::linearize(List* const list, size_t newCapacity) {
    assert(list);

    if (newCapacity < list->size)
        newCapacity = list->size;

    ListElem* newBufferElem = (ListElem*)calloc(newCapacity + 1, sizeof(ListElem));
    void* newBufferValue = calloc(newCapacity + 1, list->elemSize);

    if (!newBufferElem)  return Error::MEM_ERR;
    if (!newBufferValue) return Error::MEM_ERR;

    for (size_t index = 1; index < newCapacity + 1; ++index) {
        ListElem* elem = &newBufferElem[index];

        if (index > 1)
            elem->prev = index - 1;
        else
            elem->prev = 0;
        if (index != newCapacity)
            elem->next = index + 1;
        else
            elem->next = 0;
    }

    if (list->size) {
        assert(list->size <= list->capacity);

        ListIterator iterator{};
        List::Error err = List::begin(list, &iterator);
        assert(!err);

        uint8_t* elemValue = (uint8_t*)newBufferValue;

        do {
            elemValue += list->elemSize;
            memcpy(elemValue, ListIterator::getValue(list, &iterator), list->elemSize);
        } while (!ListIterator::next(list, &iterator));

        newBufferElem[list->size].next = 0;

        newBufferElem[0].prev = list->size;
        newBufferElem[0].next = 1;

        if (list->size < newCapacity) {
            newBufferElem[list->size + 1].prev = 0;
            list->freeTail = list->size + 1;
        } else {
            list->freeTail = 0;
        }
    } else {
        list->freeTail = 1;
        newBufferElem[0].prev = 0;
        newBufferElem[0].next = 0;
    }

    free(list->bufferElem);
    free(list->bufferValue);
    list->bufferElem = newBufferElem;
    list->bufferValue = newBufferValue;
    list->capacity = newCapacity;

    return Error::OK;
}

/**
 * @brief Resize list's buffer (could only **increase** capacity)
 *
 * @param [out] list List
 * @param [int] newCapacity New capacity of list
 * @return List::Error Error code
 */
List::Error List::resize(List* const list, size_t newCapacity) {
    assert(list);

    if (newCapacity < list->capacity)
        return Error::BUF_OVERFLOW;

    list->bufferElem = (ListElem*)realloc(list->bufferElem, (newCapacity + 1) * sizeof(ListElem));
    list->bufferValue = realloc(list->bufferValue, (newCapacity + 1) * list->elemSize);

    if (!list->bufferElem)  return Error::MEM_ERR;
    if (!list->bufferValue) return Error::MEM_ERR;

    for (size_t index = list->capacity + 1; index < newCapacity + 1; ++index) {
        ListElem* elem = &list->bufferElem[index];
        memset((uint8_t*)list->bufferValue + list->elemSize * index, 0, list->elemSize);

        if (index > list->capacity + 1)
            elem->prev = index - 1;
        else
            elem->prev = 0;
        if (index != newCapacity)
            elem->next = index + 1;
        else
            elem->next = 0;
    }

    if (list->freeTail) {
        assert(!list->bufferElem[list->freeTail].prev);
        list->bufferElem[list->freeTail].prev = newCapacity;
        list->bufferElem[newCapacity].next = list->freeTail;
    } else {
    }
    list->freeTail = list->capacity + 1;
    list->capacity = newCapacity;

    return Error::OK;
}

#define HEAD (list->bufferElem[0].prev)
#define TAIL (list->bufferElem[0].next)
#define FREETAIL (list->freeTail)
#define _NEXT(elem) (list->bufferElem[elem].next)
#define _PREV(elem) (list->bufferElem[elem].prev)
#define IT (iterator->ptr)

#define MAKE_NEW_ELEMENT                    \
    if (!FREETAIL) {                         \
        assert(list->size == list->capacity); \
        return Error::BUF_OVERFLOW;            \
    }                                           \
    assert(list->size < list->capacity);         \
    size_t newElem = FREETAIL;                    \
    FREETAIL = _NEXT(FREETAIL);                    \
    if (FREETAIL)                                   \
        _PREV(FREETAIL) = 0;

#define SET_ELEM_VALUE(it, func, src) \
    mem##func((uint8_t*)list->bufferValue + list->elemSize * it, src, list->elemSize)

#define SET_NEW_ELEMENT                 \
    list->size++;                        \
    if (src)                              \
        SET_ELEM_VALUE(newElem, cpy, src); \
    else                                    \
        SET_ELEM_VALUE(newElem, set, 0);

/**
 * @brief Push new element to the back of the list
 *
 * @param [out] list List
 * @param [in] src Pointer to the new element value
 * @return List::Error Error code
 */
List::Error List::pushBack(List* const list, void const* const src) {
    assert(list);

    ListIterator it{};
    it.ptr = 0;

    return insertBefore(list, &it, src);
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

    ListIterator it{};
    it.ptr = 0;

    return insertAfter(list, &it, src);
}

/**
 * @brief Pop an element from the back of the list
 *
 * @param [out] list List
 * @return List::Error Error code
 */
List::Error List::popBack(List* const list) {
    assert(list);

    ListIterator it{};
    it.ptr = HEAD;

    return erase(list, &it, Direction::BACKWARD);
}

/**
 * @brief Pop an element from the front of the list
 *
 * @param [out] list List
 * @return List::Error Error code
 */
List::Error List::popFront(List* const list) {
    assert(list);

    ListIterator it{};
    it.ptr = TAIL;

    return erase(list, &it, Direction::FORWARD);
}

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

    MAKE_NEW_ELEMENT;

    assert(_PREV(_NEXT(IT)) == IT);

    _PREV(newElem) = IT;
    _NEXT(newElem) = _NEXT(IT);

    _PREV(_NEXT(IT)) = newElem;
    _NEXT(IT) = newElem;

    SET_NEW_ELEMENT;

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

    ListIterator it{};
    it.ptr = _PREV(iterator->ptr);

    return insertAfter(list, &it, src);
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
    assert(list);
    assert(iterator);
    assert(IT);

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

    assert(_NEXT(_PREV(IT)) == IT);
    assert(_PREV(_NEXT(IT)) == IT);

    size_t elemToSet = 0;
    switch (direction) {
    case Direction::FORWARD:
        elemToSet = _NEXT(IT);
        break;
    case Direction::BACKWARD:
        elemToSet = _PREV(IT);
        break;
    default:
        assert(0);
    }

    SET_ELEM_VALUE(IT, set, 0);
    _PREV(FREETAIL) = IT;
    _NEXT(IT) = FREETAIL;
    _PREV(IT) = 0;
    FREETAIL = IT;

    IT = elemToSet;

    return Error::OK;
}

/**
 * @brief Is list empty
 *
 * @param [in] list List
 */
bool List::isEmpty(List const* const list) {
    assert(list);
    return !list->size;
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
    assert(list->bufferElem);

    IT = TAIL;

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
    assert(list->bufferElem);

    IT = HEAD;

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

    List::begin(list, iterator);
    size_t counter = 0;
    while (counter < index && !ListIterator::next(list, iterator)) {
        counter++;
    }

    if (counter != index) {
        IT = 0;
        return Error::OUT_OF_SIZE;
    }

    return Error::OK;
}

#undef HEAD
#undef TAIL
#undef FREETAIL
#undef _NEXT
#undef _PREV
#undef IT
#undef SET_ELEM_VALUE
#undef SET_NEW_ELEMENT
#undef MAKE_NEW_ELEMENT

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
