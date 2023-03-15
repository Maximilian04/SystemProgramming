#include         "StackArr.h"
#define TESTNAME "StackArr  Test 1"

#include "include.h"

int main() {
    TIMEPOINT(tpBegin);

    size_t size = 0;
    int a = 239;

    // Stack* stack = Stack::stack_ctr((size_t)1e6, sizeof(int));
    Stack* stack = Stack::stack_ctr(sizeof(int));
    if (!stack) ERROR("CTOR");

    while (size < 1e6) {
        if (!Stack::push(stack, &a)) ERROR("PUSH, size = " << size);
        size++;
    }
    for (int i = 0; i < 9; ++i) {
        // cout << i << "/9 done" << endl;

        size_t  half = size >> 1;
        for (int j = 0; j < half; ++j) {
            if (!Stack::pop(stack)) ERROR("POP, size = " << size << " i = " << i << " j = " << j);
            size--;
        }
        half >>= 1;
        for (int j = 0; j < half; ++j) {
            if (!Stack::push(stack, &a)) ERROR("PUSH, size = " << size << " i = " << i << " j = " << j);
            size++;
        }
    }

    TIMEPOINT(tpEnd);

    LOG(chrono::duration_cast<chrono::milliseconds>(tpEnd - tpBegin).count() << " ms");

    cout << "Program finished 0" << endl;
}
