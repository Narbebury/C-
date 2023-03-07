/* Diseñe un programa, que muestre el mayor y el menor de
tres introducidos por el usuario. Desarrolle 02 funciones. */
#include <stdio.h>

//PROPÓSITO
int maximo(int, int, int);
int minimo(int, int, int);

void main()
{
    //LLAMADA
    int numero1, numero2, numero3;
    printf("Introduzca 3 n%cmeros:\n", 163);
    scanf("%i %i %i", &numero1, &numero2, &numero3);
    printf("\nEl m%cximo es: %i", 160, maximo(numero1, numero2, numero3));
    printf("\nEl m%cnimo es: %i", 161, minimo(numero1, numero2, numero3));
}

//DEFINICIÓN
int maximo(int x, int y, int z)
{
    int max = x;
    if (y > max)
    {
        max = y;
    }
    if (z > max)
    {
        max = z;
    }

    return max;
}

int minimo(int x, int y, int z)
{
    int min = x;
    if (y < min)
    {
        min = y;
    }
    if (z < min)
    {
        min = z;
    }
    
    return min;
}
