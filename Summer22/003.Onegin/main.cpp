#include <stdio.h>

#include "pervert.h"

int main() {
    FILE* filer = fopen("EvgeniyOnegin.txt", "r");
    char str[256];
    fscanf(filer, "%[^\n]", str);
    fclose(filer);

    FILE* file = fopen("file.txt", "w");
    fprintf(file, "Also Слухов про него ходило много.\n'%s'\nBut he was killed\n", str);
    fclose(file);

    pervert::readListOfLines();
    pervert::destroyListOfLines();

    return 0;
}
