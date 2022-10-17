#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>


typedef uint8_t TYPE;

int main() {
    TYPE a = 9;
    TYPE b = 9;
    TYPE c = 9;
    TYPE d = 9;
    TYPE e = 9;
    TYPE f = 9;
    TYPE g = 9;
    TYPE h = 9;
    TYPE i = 9;
    TYPE j = 9;
    TYPE k = 9;

    /*printf("* %p\n", &a);
    printf("* %p\n", &b);
    printf("* %p\n", &c);
    printf("* %p\n", &d);
    printf("* %p\n", &e);
    printf("* %p\n", &f);
    printf("* %p\n", &g);
    printf("* %p\n", &h);
    printf("* %p\n", &i);
    printf("* %p\n", &j);
    printf("* %p\n", &k);*/

    printf("%u\t", a);
    printf("%u\t", b);
    printf("%u\t", c);
    printf("%u\t", d);
    printf("%u\t", e);
    printf("%u\t", f);
    printf("%u\t", g);
    printf("%u\t", h);
    printf("%u\t", i);
    printf("%u\t", j);
    printf("%u\n", k);
    scanf("%" SCNu8, &a);
    printf("%u\t", a);
    printf("%u\t", b);
    printf("%u\t", c);
    printf("%u\t", d);
    printf("%u\t", e);
    printf("%u\t", f);
    printf("%u\t", g);
    printf("%u\t", h);
    printf("%u\t", i);
    printf("%u\t", j);
    printf("%u\n", k);

    return 0;
}