#include <stdio.h>

int main()
{
    int y = 10,x;
    x = y+6;
    printf("El valor es: %d\n",x);

    //otra forma de usar el operador coma:
    int z=10,m;
    m=(z=6, z+10);//Realizo la operacion
    printf("El valor de m es: %d",m);


    return 0;
}