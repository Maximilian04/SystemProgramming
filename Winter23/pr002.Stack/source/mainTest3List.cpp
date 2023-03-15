#include         "StackList.h"
#define TESTNAME "StackList Test 3"

#include "include.h"

int main() {
    TIMEPOINT(tpBegin);

    size_t size = 0;
    int a = 239;

    Stack* stack = Stack::stack_ctr(sizeof(int));
    if (!stack) ERROR("CTOR");

    // for (int i = 0; i < 1e3; ++i) {
        // cout << i << "/1000" << endl;
    for (int i = 0; i < 1e2; ++i) {
        for (int i = 0; i < 1e6; ++i) {
            if (!Stack::push(stack, &a)) ERROR("PUSH, size = " << size);
            size++;
        }
    }
    for (int i = 0; i < 1e2; ++i) {
        // cout << i << "/1000" << endl;
        for (int i = 0; i < 1e6; ++i) {
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
