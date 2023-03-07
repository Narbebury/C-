/*Programa para una estructura que guarde los datos de los 10 alumnos de la materia programación, y los muestres por pantalla, la estructura debe tener
(documento, nombre, apellido, edad y Mail)*/
#include <stdio.h>

struct alumno
{
    char nombre[20];
    char apellido[20];
    int edad;
    int documento;
    char mail[50];
};

void carga(char, char, int, int, char);

void main()
{
    struct alumno vector[10];

    for (int i = 0; i < 10; i++)
    {

        char Nom[20];
        char Ape[20];
        int ED;
        int Doc;
        char M[50];
        
        printf("Alumno Nro %d\n", i + 1);
        printf("Ingrese el Nombre: ");
        scanf("%c", Nom);
        strcpy(vector[i].nombre, Nom);

        printf("Ingrese el Apellido: ");
        scanf("%c", Ape);
        strcpy(vector[i].apellido, Ape);

        printf("Ingrese la Edad: ");
        scanf("%i", &ED);
        vector[i].edad = ED;
        printf("\n");

        printf("Ingrese el Documento: ");
        scanf("%i", &Doc);
        vector[i].documento = Doc;
        printf("\n");

        printf("Ingrese el mail: ");
        scanf("%i", &M);
        vector[i].edad = M;
        printf("\n");
    }

    for (int i = 0; i < 10; i++)
    {
        printf("Alumno: %i \n", i + 1);
        printf("Apellido: %s \n", vector[i].apellido);
        printf("Edad: ", vector[i].edad);
        printf("Documento: ", vector[i].documento);
        printf("Mail: ", vector[i].mail);
    }
}
