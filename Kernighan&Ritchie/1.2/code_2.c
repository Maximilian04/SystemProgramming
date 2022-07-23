#include <stdio.h>

/* печать таблицы температур по Фаренгейту
и Цельсию для fahr = 0, 20, ... , 300 */

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;   /* нижняя граница таблицы температур */
    upper = 300; /* верхняя граница */
    step = 20;   /* шаг */

    fahr = lower;

    while (fahr <= upper) {
        celsius = 5.0 / 9 * (fahr - 32.0);
        printf("%4.1f%7.2f %%\n", fahr, celsius);
        fahr = fahr + step;
    }
}
