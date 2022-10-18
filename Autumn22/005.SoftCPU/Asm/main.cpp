#include <stdio.h>
#include <assert.h>
#include <stdint.h>

#include "ui.h"

int main(const int argc, const char* const* const argv) {
    ListOfLines asmText{};
    if (ui::handleFlags(argc, argv, &asmText))
        return 1;

    AsmCode asmCode{};
    FixupsTable fixupsTable{};
    if (ui::translateAsm(&asmText, &asmCode, &fixupsTable))
        return 1;
    if (ui::translateAsm(&asmText, &asmCode, &fixupsTable))
        return 1;

    ui::writeAsmCode2File(&asmCode);
    asmCode::freeBuf(&asmCode);
    fixupsTable::freeTable(&fixupsTable);

    return 0;
}
