#include <stdio.h>

/* печать таблицы температур по Фаренгейту
и Цельсию для fahr = 0, 20, ... , 300 */

int main() {
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;   /* нижняя граница таблицы температур */
    upper = 300; /* верхняя граница */
    step = 20;   /* шаг */

    fahr = lower;

    while (fahr <= upper) {
        celsius = (fahr - 32) * 5 / 9;
        printf("%2d%6d %%\n", fahr, celsius);
        fahr = fahr + step;
    }
}
