#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*b)Cargamos alumnos
Solicitar al usuario el ingreso de: apellido y nombre de 5 alumnos, los que serán guardados en una matriz.
Al finalizar la carga, los datos deberán ser resguardados en un archivo de texto utilizando una función Guardar() que reciba como parámetro la matriz.
Condiciones
•	Archivo tipo texto, nombre: alumnos.txt
•	Grabar archivo por flujos, un alumno por fila
•	Si el archivo contiene alumnos, se debe agregar al final*/

struct alumno
{
    char Apellido[40];
    char Nombre[40];
} matriz[5][1];

void Guardar()
{

    FILE *archivo = fopen("alumnos.txt", "a+");

    if (archivo == NULL)
    {
        printf("Error al intentar abrir el archivo");
        exit(1);
    }
    else
    {
        struct alumno;

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                printf("Ingrese el apellido del alumno: \n");
                scanf("%s", &matriz[i][j].Apellido);
                printf("\nIngrese el nombre del alumno: ");
                scanf("%s", &matriz[i][j + 1].Nombre);
            }
        }

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 1; j++)
            {
                fprintf(archivo, "%s,", matriz[i][j].Apellido);
                fprintf(archivo, "%s\n", matriz[i][j + 1].Nombre);
            }
        }
        fclose(archivo);
    }
}

int main()
{

    Guardar();
}