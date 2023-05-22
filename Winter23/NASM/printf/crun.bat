:: nasm printfm.asm -f win64

:: ld hello.obj "C:\Windows\System32\kernel32.dll" "C:\Windows\System32\user32.dll" -e __start
:: a.exe

nasm printfm.asm -f win64
nasm asmMain.asm -f win64
nasm callPrintfm.asm -f win64
g++ -c main.cpp -o main.obj
g++ -S -c main.cpp -O0
g++ printfm.obj asmMain.obj callPrintfm.obj main.obj -o printfTest
