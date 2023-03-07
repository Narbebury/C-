/*	Ingresar por teclado un valor mayor a 10 y calcular la sumatoria
del mismo en una funcion invocada en forma recursiva.*/

#include <stdio.h>

int sumatoria(int);

main()
{
    int i=0;

    printf("Ingrese un numero: \n");
    scanf("%d",&i);
    
    while (i < 10)
    {
        printf("El numero ingresado es incorrecto \n");
        scanf("%d",&i);
    }
    
    printf("La sumatoria del numero ingresado es: %d \n",sumatoria(i));   
}

int sumatoria(int i)
{
    if (i==1)
    {
        return 1;
    }
    else
    {
        return sumatoria (i-1)+i;
    }
}
