#include <stdio.h>

#include "tests.h"
#include <List.h>

int main(int argc, const char* const* const argv) {
    testingSystem::main(argc, argv);
    List list;
    List__ctor(list, int, "%d");
    List__dump(list);
    int i = 1;
    List::pushBack(&list);
    List::pushBack(&list, &i);
    i = -1;
    List::pushFront(&list, &i);
    i = -2;
    List::pushFront(&list, &i);
    i = -3;
    List::pushFront(&list, &i);
    i = -4;
    List::pushFront(&list, &i);
    i = -5;
    List::pushFront(&list, &i);
    i = -6;
    List::pushFront(&list, &i);
    List__dump(list);

    ListIterator getter{};
    List::set2index(&list, &getter, 3);
    logger::logMsg(strFParser::parseFCalloc(COLORED_TEXT("lime", "element №3 : '%d'"), *(int*)ListIterator::getValue(&getter)));

    List::popBack(&list);
    List__dump(list);
    List::popFront(&list);
    List__dump(list);

    ListIterator elem{};
    List::begin(&list, &elem);
    List::erase(&list, &elem);
    List__dump(list);
    List::begin(&list, &elem);
    ListIterator::next(&elem);
    ListIterator::next(&elem);
    ListIterator::next(&elem);
    ListIterator::next(&elem);
    ListIterator::prev(&elem);
    List::erase(&list, &elem);
    List__dump(list);

    List::dtor(&list);
    List__dump(list);

    return 0;
}
