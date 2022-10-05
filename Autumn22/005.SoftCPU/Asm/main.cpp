#include <stdio.h>
#include <assert.h>

#include "ui.h"

int main(const int argc, const char* const* const argv) {
    ui::handleFlags(argc, argv);

    ui::closeInputFile();
    return 0;
}
