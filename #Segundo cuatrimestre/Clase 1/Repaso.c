/*
Desarrolle el siguiente programa que solicite al usuario el ingreso de los lados L1 y L2 de una figura geométrica. 
Para calcular su perímetro, deberá llamarse a una función Perímetro que retorno dicho valor. 
La función Perímetro deberá identificar si se trata de un cuadrado (L1 = L2) o un rectángulo (L1 != L2) y 
llamar a la función PCuadrado() o PRectangulo() según corresponda, 
informando los lados L1 y L2 para calcular y retornar el perímetro de la figura. 
El resultado del perímetro deberá mostrarse desde la función Principal.
*/


#include <stdio.h>

int Area(int, int);
int ACuadrado(int, int);
int ARectangulo(int, int);
int l1;
int l2;

void main()
{
    printf("Ingrese l1:" );
    scanf("%i", &l1);
    printf("Ingrese l2: ");
    scanf("%i", &l2);

    printf("%area: %i \n", 181, Area(l1,l2));
}

int ACuadrado(int l1, int l2)
{
    return l1 * l2;
}

int ARectangulo(int l1, int l2)
{
    return l1 * l2;
}
