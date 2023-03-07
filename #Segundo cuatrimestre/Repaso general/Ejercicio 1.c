// Defina una función que reciba 2 caracteres y devuelva la concatenación de los mismos.
#include <stdio.h>
#include <string.h>

//void Caracteres();

int main(void)
{
    void Concatenar(char caract1[],char caract2[],char destino[]);
    char Carac1[1],Carac2[1],Concatenacion[3];
    printf("Ingrese 2 caracteres");
    scanf("%s %s",Carac1,Carac2);
    Concatenar(Concatenacion, Carac1, Carac2);

    printf("La concatenacion de los caracteres es: %s",Concatenacion);
    return 0;
}

Void Concatenar(char caract1[],char caract2[],char destino[])