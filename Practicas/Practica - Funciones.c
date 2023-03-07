#include <stdio.h>

int pow(int Arg, int exp); //Prototipo
        //argumentos de la función

int main()
{
    int res = pow(2, 3);
    
    printf("El valor de 2 al cubo es: %d\n",res);
    return 0;
}

int pow(int Arg, int exp)
{
    int i;
    int res = 1;
    for (i = 0; i < exp; i++)
    {
        res *= Arg;
    }

    return res;
}