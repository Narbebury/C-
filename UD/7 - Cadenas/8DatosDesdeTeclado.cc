#include <stdio.h>


struct personas{
    char Nombre[80];
    char Apellido[80];
    int edad;
};

int main()
{
    struct personas DatosPersonas[3];

    printf("Por favor introcude 3 nombres de tu familia: ");
    
    for (int i = 0; i < 3; i++)
    {
        printf("Persona Nro %d",i+1);
        printf("Nombre: ");
        gets_s(DatosPersonas[i]->Nombre);
    }
    

    return 0;
}