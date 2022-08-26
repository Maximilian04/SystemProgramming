#include <stdio.h>
#include <Windows.h>

#include "strLib.h"

const int COMMANDLINE_BUFFER_SIZE = 128;

int main() {
    printf("Program provide you to test strLib functions\n"
        "Please print function name and input for test:\n");

    system(".\\build\\tests.exe -i");

    return 0;
}
