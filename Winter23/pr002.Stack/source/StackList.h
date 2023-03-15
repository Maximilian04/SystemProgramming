#ifndef CLASSSTACK
#define CLASSSTACK

class Stack {
public:
    struct StackElem {
        void* data;
        StackElem* prev;
    };

    static Stack* stack_ctr(size_t element_size);
    static int push(Stack* st, void* buffer);
    static int top(Stack* st, void* buffer);
    static int pop(Stack* st);
    static Stack* stack_dtr(Stack* st);

private:
    StackElem head;
    size_t elemSize;

    static void Stack::stack_elem_dtr(StackElem* ptr);
};

#endif // CLASSSTACK
