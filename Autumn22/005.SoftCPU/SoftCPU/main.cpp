#include "ui.h"

int main(const int argc, const char* const* const argv) {
    CPU mainCPU = {};
    CPU__ctor(mainCPU));

    ui::Error result = ui::handleFlags(argc, argv, &mainCPU);
    if (!result)
        result = ui::runProgram(&mainCPU);
    // CPU__dump(mainCPU));
    cpu::dtor(&mainCPU);

    if (result)
        return 1;

    return 0;
}
