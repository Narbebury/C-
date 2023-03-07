#include <stdio.h> //standar input-output header
#define PI 3.1416

int main()
{
    printf("El valor de la constante PI es: %.4f\n", PI);

    const int edad = 20;
    printf("La edad de Juan es: %d\n", edad);

    enum personas
    {
        carlos,  //0
        maria,   //1
        jose,    //2
        ernesto, //3
        raul     //4

    }
    p1, p2, p3, p4, p5;
    p1 = carlos;
    p2 = maria;
    p3 = jose;
    p4 = ernesto;
    p5 = raul;

    printf("%d", p3);
    return 0;
}