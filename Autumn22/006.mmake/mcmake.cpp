#include <stdio.h>

int main(int argc, char* argv[]) {
    FILE* mcmakefile = fopen("mcmakefile", "rt");
    if (!mcmakefile) {
        printf("Cannot open mcmakefile\n");
        return 1;
    }

    if (fscanf(mcmakefile, "all: ") != 0) {
        printf("Incorrect 'all:' line in mcmakefile\n");
        return 1;
    }

    if (fclose(mcmakefile)) {
        printf("Cannot close correctly file\n");
        return 1;
    }
    return 0;
}