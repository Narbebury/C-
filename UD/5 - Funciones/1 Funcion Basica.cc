#include <stdio.h>

int sumar(int, int);

int main()
{
    int op1, op2, resultado;
    op1 = 10;
    op2 = 5;
    resultado = sumar(op1, op2);
    printf("El resultado de la suma entre %d y %d es: %d\n", op1, op2, resultado);

    printf("El resultado de la suma entre %d y %d es: %d", 100, 10, sumar(100,10));
    return 0;
}

int sumar(int op1, int op2)
{
    return op1 + op2;
}