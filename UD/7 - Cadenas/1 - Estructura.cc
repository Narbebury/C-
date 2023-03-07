#include <stdio.h>

struct coche
{
    char Marca[100];
    char Modelo[100];
    char color[100];
    int anio;
};

int main()
{
    struct coche coche1;
    printf("El tamanio de la estructura de el coche es %d bytes\n",sizeof(coche1));

    struct coche coche1 ={"Audi","TT","Azul",1988};
    printf("Mi coche favorito es : %s de color %s",coche1.)



    return 0;
}