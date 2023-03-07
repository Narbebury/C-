#include <stdio.h>
int suma(int, int, int); /*Prototipo*/

int suma(int num1, int num2, int resultado)
{
    num1 = 10;
    num2 = 5;
    resultado = num1 + num2;
    return resultado;
}

int main()
{
    int a = 10, b = 5;
    int resultado;
    resultado = suma(a, b, resultado);
    printf("Resultado de %d y %d es : %d", a, b, resultado);

    return 0;
}