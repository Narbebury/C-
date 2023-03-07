#include <stdio.h>

int main()
{
    int a;
    float b;
    double c;
    short int d;
    long e;

    printf("La longitud en bytes de int es: %d\n", sizeof(a));
    printf("La longitud en bytes de float es: %d\n", sizeof(b));
    printf("La longitud en bytes de double es: %d\n", sizeof(c));
    printf("La longitud en bytes de short int es: %d\n", sizeof(d));
    printf("La longitud en bytes de long es: %d", sizeof(e));
    
    return 0;
}