#include <..\..\004.Stack\StackLib\StackLibWorld.h>

#include "ui.h"
#include "cpu.h"

int main(const int argc, const char* const* const argv) {
    CPU mainCPU = {};

    asmCode::createBuf(&mainCPU.code);
    ui::Error result = ui::handleFlags(argc, argv, &mainCPU.code);
    if (!result)
        result = ui::runProgram(&mainCPU);
    asmCode::freeBuf(&mainCPU.code);

    if (result)
        return 1;

    return 0;
}
