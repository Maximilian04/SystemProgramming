#include <assert.h>
#include <stdio.h>

#include "..\logger\logger.h" //TODO: WTF???

#include "Stack.h"

namespace stack {
    /**
     * @brief Stack constructor
     *
     * @param [out] stack Stack
     * @param [in] capacity Init capacity
     */
    void ctor(Stack* stack, size_t capacity) {

        stack->size = 0;
        stack->capacity = capacity;
        stack->data = (Elem_t*)calloc(capacity, sizeof(Elem_t));
        assert(stack->data != nullptr);
    }

    /**
     * @brief Stack destructor
     *
     * @param [out] stack Stack
     */
    void dtor(Stack* stack) {
        free(stack->data);
    }

    /**
     * @brief Push element to stack
     *
     * @param [in] stack Stack
     * @param [in] elem Element
     */
    void push(Stack* stack, Elem_t elem) {

        assert(stack->size < stack->capacity);
        stack->data[stack->size] = elem;
        stack->size++;
    }

    /**
     * @brief Dump Stack info
     *
     * @param [in] stack Stack
     */
    void dump(Stack* stack) {
        FILE* logFile = fopen("log1.html", "at");

        logger::logHtmlHead(logFile);
        fprintf(logFile,
            "<p> <div>stack::push() at Stack.cpp (30 line)</div></p>\n"
            "<p> <div>Stack[<font color=\"cyan\">0x005860</font>] \"stack1\" at main() at main.cpp (50 line):</div></p>\n"
            "<p> <div style=\"margin-left:4ch\">{</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:4ch\">size</div>\n"
            "    <div style=\"margin-left:15ch\">= 5</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:4ch\">capacity</div>\n"
            "    <div style=\"margin-left:15ch\">= 5</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:4ch\">data[<font color=\"cyan\">0x005320</font>]:</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:8ch\">{</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:8ch\">[0]</div>\n"
            "    <div style=\"margin-left:7ch\">*</div>\n"
            "    <div style=\"margin-left:12ch\">= 1</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:8ch\">[1]</div>\n"
            "    <div style=\"margin-left:7ch\">*</div>\n"
            "    <div style=\"margin-left:12ch\">= 2</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:8ch\">[2]</div>\n"
            "    <div style=\"margin-left:7ch\">*</div>\n"
            "    <div style=\"margin-left:12ch\">= 3</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:8ch\">[3]</div>\n"
            "    <div style=\"margin-left:12ch\">= NAN (POISON)</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:8ch\">[4]</div>\n"
            "    <div style=\"margin-left:12ch\">= NAN (POISON)</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:8ch\">}</div>\n"
            "</p>\n"
            "<p> <div style=\"margin-left:4ch\">}</div>\n"
            "</p>\n"
        );
        logger::beginBlock(logFile);
        logger::logStr(logFile, "qwerty 1");
        logger::logStr(logFile, "qwerty 2");
        logger::beginBlock(logFile);
        logger::logStr(logFile, "qwerty 2+1");
        logger::endBlock(logFile);
        logger::logStr(logFile, "qwerty 0");
        logger::endBlock(logFile);
        logger::logHtmlTail(logFile);

        fclose(logFile);
    }
}
