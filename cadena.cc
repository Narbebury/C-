#include <stdio.h>
#include <string.h>

int main()
{
    char Cadena1[20];
    char Cadena2[20];

    printf("Ingrese su Nombre: ");
    scanf("%s", Cadena1);
    printf("\nIngrese su Apellido: ");
    scanf("%s", Cadena2);

    printf("Su nombre es: %s", strcat(strcat(Cadena2, ","), Cadena1));
    
    return 0;
}