#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[100];
    char* name = (char*)calloc(100, sizeof(char));
    scanf("%s", input);
    scanf("%s", input);
    printf("enter text:\n");
    scanf("\n%5[^\n]", name);
    printf("'%s'", name);

    return 0;
}