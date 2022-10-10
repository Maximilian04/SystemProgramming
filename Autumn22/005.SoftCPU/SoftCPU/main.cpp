#include <..\..\004.Stack\StackLib\StackLibWorld.h>

#include "ui.h"
#include "cpu.h"

int main(const int argc, const char* const* const argv) {
    CPU cpu1 = {};
    
    if (ui::handleFlags(argc, argv, &cpu1.code))
        return 1;

    return 0;
}
