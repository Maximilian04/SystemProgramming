#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "ui.h"

int main(const int argc, const char* const* const argv) {
    ListOfLines asmText{};
    if (ui::handleFlags(argc, argv, &asmText))
        return 1;

    AsmCode asmCode{};
    if (ui::translateAsm(&asmText, &asmCode))
        return 1;

    return 0;
}
