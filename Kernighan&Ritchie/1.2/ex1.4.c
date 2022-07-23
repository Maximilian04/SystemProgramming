#include <stdio.h>

/* печать таблицы температур по Фаренгейту
и Цельсию для fahr = 0, 20, ... , 300 */

int main() {
    printf("celsius: fahr:\n");

    for (float celsius = -20; celsius <= 150; celsius += 10) {
        float fahr = (celsius + 32.0) / (5.0f / 9.0f);
        printf("%8.1f%6.1f\n", celsius, fahr);
    }
}
