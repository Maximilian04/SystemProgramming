#include "stdio.h"

extern "C" void asmMain();

int main() {
    printf("normal printf%d%d%d%d%d\n\n", 0, 0, 0, 0, 0);

    asmMain();
    
    printf("normal printf%d%d%d%d%d\n\n", 7, 7, 7, 7, 7);

    return 0;
}

/*
D:\programming\SystemProgramming\Winter23\NASM\printf>nasm printfm.asm -f win64

D:\programming\SystemProgramming\Winter23\NASM\printf>g++ -c main.cpp -o main.obj

D:\programming\SystemProgramming\Winter23\NASM\printf>g++ printfm.obj main.obj example.obj -o main

D:\programming\SystemProgramming\Winter23\NASM\printf>main.exe
*/
