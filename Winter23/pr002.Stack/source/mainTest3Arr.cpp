#include         "StackArr.h"
#define TESTNAME "StackArr  Test 3"

#include "include.h"

int main() {
    TIMEPOINT(tpBegin);

    size_t size = 0;
    int a = 239;

    // Stack* stack = Stack::stack_ctr((size_t)1e6, sizeof(int));
    Stack* stack = Stack::stack_ctr(sizeof(int));
    if (!stack) ERROR("CTOR");

    while (size < 1e9) {
        if (!Stack::push(stack, &a)) ERROR("PUSH, size = " << size);
        size++;
    }
    for (int i = 0; i < 1e4; ++i) {
        // cout << i << "/10000" << endl;
        for (int i = 0; i < 1e5; ++i) {
            if (randGenerator() % 2) {
                if (!Stack::push(stack, &a)) ERROR("PUSH, size = " << size);
                size++;
            } else {
                if (!Stack::pop(stack)) ERROR("POP, size = " << size);
                size--;
            }
        }
    }

    TIMEPOINT(tpEnd);

    LOG(chrono::duration_cast<chrono::milliseconds>(tpEnd - tpBegin).count() << " ms");

    cout << "Program finished 0" << endl;
}
