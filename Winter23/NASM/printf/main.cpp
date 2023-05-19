#include <stdio.h>
#include <cstdarg>

extern "C" void asmMain();
extern "C" void callPrintfm(const char* format, ...);

// void func(int i, ...) {
//     va_list args;
//     va_start(args, i);
//     vprintf("ququ%d\n", args);
//     va_end(args);
// }

int main() {
    // printf("No segfault) %d%d%d%d%d\n\n", 0, 0, 0, 0, 0);

    asmMain();
    
    // printf("\nNo segfault) %d%d%d%d%d\n", 7, 7, 7, 7, 7);

    callPrintfm("%s-%s-%s-%s-%s", "aaa", "bbb", "ccc", "ddd", "eee");

    // printf("\nNo segfault) %d%d%d%d%d\n", 8, 8, 8, 8, 8);

    // func(0, 1, 2, 3);

    return 0;
}

/*
D:\programming\SystemProgramming\Winter23\NASM\printf>nasm printfm.asm -f win64

D:\programming\SystemProgramming\Winter23\NASM\printf>g++ -c main.cpp -o main.obj

D:\programming\SystemProgramming\Winter23\NASM\printf>g++ printfm.obj main.obj example.obj -o main

D:\programming\SystemProgramming\Winter23\NASM\printf>main.exe
*/
