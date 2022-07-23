#include <stdio.h>

/* печать таблицы температур по Фаренгейту
и Цельсию для fahr = 0, 20, ... , 300 */

int main() {
    printf("fahr: celsius:\n");

    for (float fahr = 0; fahr <= 300; fahr += 20) {
        float celsius = 5.0 / 9 * (fahr - 32.0);
        printf("%5.1f%9.4f\n", fahr, celsius);
    }
}
