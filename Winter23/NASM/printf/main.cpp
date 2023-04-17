
extern "C" void asmFunction();
extern "C" void callPrintf();
extern void example();

int main() {
    asmFunction();
    callPrintf();
    example();

    return 0;
}

/*
D:\programming\SystemProgramming\Winter23\NASM\printf>nasm printfm.asm -f win64

D:\programming\SystemProgramming\Winter23\NASM\printf>g++ -c main.cpp -o main.obj

D:\programming\SystemProgramming\Winter23\NASM\printf>g++ printfm.obj main.obj example.obj -o main

D:\programming\SystemProgramming\Winter23\NASM\printf>main.exe
*/
