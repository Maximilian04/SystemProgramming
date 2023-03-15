#ifndef CLASSSTACK
#define CLASSSTACK

class Stack{
public:
    static Stack* stack_ctr(size_t size, size_t element_size);
    static Stack* stack_ctr(size_t size);
    static int push(Stack* st, void* buffer);
    static int top(Stack* st, void* buffer);
    static int pop(Stack* st);
    static Stack* stack_dtr(Stack* st);
private:
    void* data;
    size_t elemSize;
    size_t capacity;
    size_t size;

    static int Stack::stack_realloc(Stack* st);
};

#endif // CLASSSTACK
