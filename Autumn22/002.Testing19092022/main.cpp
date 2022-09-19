#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <clocale>
#include <Windows.h>

_off_t getSizeOfFile(const char* fileName);
size_t readFileToBuffer(const char* fileName, char** buffer);

_off_t getSizeOfFile(const char* fileName) {
    struct stat fileStat = {};

    int statResult = stat(fileName, &fileStat);
    assert(statResult == 0 && "Cannot get file info");

    return fileStat.st_size;
}

size_t readFileToBuffer(const char* fileName, char** buffer) {
    assert((*buffer) == nullptr);

    int fileSize = getSizeOfFile(fileName);

    FILE* file = fopen(fileName, "rt");
    assert(file != nullptr && "Cannot open file");

    (*buffer) = (char*)calloc(fileSize + 1, sizeof(char));
    assert((*buffer) != nullptr);

    size_t freadResult = fread((*buffer), sizeof(char), fileSize, file);
    fclose(file);

    (*buffer) = (char*)realloc((void*)(*buffer), sizeof(char) * (freadResult + 1));
    (*buffer)[freadResult] = '\0';

    return freadResult + 1;
}

int main() {
    setlocale(LC_ALL, ".1251");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    char* buffer = nullptr;
    int fileSize = (int)readFileToBuffer("text.txt", &buffer);

    int array[256] = { 0 };
    for (int i = 0; i < 256; ++i) {
        array[i] = i;
    }

    for (int a = 0; a < fileSize; ++a) {
        if (buffer[a] == '\n') continue;
        printf("symbol %2d: char:%4d; (unsigned char):%4u; %c: %d\n",
            a, buffer[a], (int)((unsigned char)buffer[a]), buffer[a], array[(unsigned char)buffer[a]]);
    }

    free(buffer);
    return 0;
}
