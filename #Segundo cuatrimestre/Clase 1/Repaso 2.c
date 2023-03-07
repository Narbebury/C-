/*Desarrolle una función que reciba una estructura del tipo Cadenas con los siguientes miembros: texto1[20] y texto2[20]. 
La función debe determinar y mostrar al usuario el mensaje correspondiente indicando cual texto es mayor o bien si son 
iguales. Considerar el desarrollo de la función Principal para solicitar al usuario el ingreso de ambos textos a comparar.
*/

#include <stdio.h>

struct Cadena
{
    char texto1[20];
    char texto2[20];
};

void Comparar(struct Cadena);

void main()
{

    struct Cadena cad;

    printf("\n Ingrese la 1er cadena:");
    scanf("%s", cad.texto1);

    printf("\n Ingrese la 2da cadena:");
    scanf("%s", cad.texto2);

    Comparar(cad);

}

void Comparar(struct Cadena cadena)
{

    switch (strcmp(cadena.texto1, cadena.texto2))
    {
    case 0:
        printf("\n las cadenas son IGUALES");
        break;
    case 1:
        printf("\n las cadenas 1 es MAYOR que la cadena 2");
        break;
    case -1:
        printf("\n las cadenas 1 es MENOR que la cadena 2");
        break;
    }
    printf("\n");
    printf("%i \n", strlen(cadena.texto1));
    printf("%i \n", strlen(cadena.texto2));

    strcpy(cadena.texto1 , cadena.texto2);
    
    printf("%i \n", strlen(cadena.texto1));
    printf("%s \n", cadena.texto1);
}
