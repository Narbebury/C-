/*a) defina una estructura del tipo fecha con los miembros dia tipo entero, mes tipo caracter y año tipo entero
b) definir una estructura del tipo Persona con los miembros apellido, nombre y fechaNacimiento del tipo fecha
c) cargar un arreglo de 5 persona 
d) Mostrar el arreglo de las 5 personas con do.. while*/

#include <stdio.h>
//a) defina una estructura del tipo fecha con los miembros dia tipo entero, mes tipo caracter y año tipo entero
struct fecha
{
    int dia;
    char mes[20];
    int anio;
};

//b) definir una estructura del tipo Persona con los miembros apellido, nombre y fechaNacimiento del tipo fecha
struct persona
{
    char apellido[25];
    char nombre[25];
    struct fecha nacimiento;
};



main()
{
//c) cargar un arreglo de 5 persona (LOcAL)
struct persona per[5];

for (int i = 0; i < 5; i++)
{
    printf("\n");
    printf("Ingrese apellido");
    printf("\n");
    scanf("%s", per[i].apellido);
    
    printf("\n");
    
    printf("Ingrese nombre");
    printf("\n");
    scanf("%s", per[i].nombre);
     
    printf("Ingrese dia");
    printf("\n");
    scanf("%i",&per[i].nacimiento.dia);

    printf("Ingrese dia");
    printf("\n");
    scanf("%s",&per[i].nacimiento.mes);

    printf("Ingrese dia");
    printf("\n");
    scanf("%i",&per[i].nacimiento.anio);
}

printf("\n");

int i=0;
do
{
    printf("%s \t", per[i].apellido);
    printf("%s \t", per[i].nacimiento.dia);
    printf("\n");
    i++;    
} while (i<=5);


}
