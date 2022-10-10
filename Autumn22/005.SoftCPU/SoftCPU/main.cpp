#include <..\..\004.Stack\StackLib\StackLibWorld.h>

#include "ui.h"

int main() {
    Stack stack1;
    STACK__ctor(stack1));

    stack::push(&stack1, 7);
    stack::push(&stack1, 13);
    stack::push(&stack1, 9);
    stack::push(&stack1, 21);
    stack::push(&stack1, 27);

    // STACK__dump(stack1));



    stack::dtor(&stack1);

    return 0;
}
