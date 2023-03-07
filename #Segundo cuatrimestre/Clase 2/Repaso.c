/*a) construya un arreglo de 5 dimensiones y otro de 5 X 5.
b) cargue la matriz con todos 0 (ceros)
c) cargue el vector con números aleatorios entre el 20 y 30
d) solicite al usuario un número entre 1 y 5
e) cargue los valores del vector en la fila de la matriz indicada por el usuario
f) muestre el contenido del vector y de la matriz
*/

#include <stdio.h>
//a) construya un arreglo de 5 dimensiones y otro de 5 X 5.
int Vector[5];
int Matriz[5][5];

main()
{

//b) cargue la matriz con todos 0 (ceros)

for (int i = 0; i < 5; i++)
{
    for (int j = 0; j < 5; j++)
    {
      Matriz[i][j]=0;  //carga con 0
    }
}

//c) cargue el vector con números aleatorios entre el 20 y 30
for(int i=0; i<5;i++)
{
    Vector[i]=rand() % 11 + 20;//Elección de números aleatorios de 21 a 30
}

//d) solicite al usuario un número entre 1 y 5
int iRespuesta;

    printf("Ingrese un numero entre 1 y 5");
    scanf("%i", &iRespuesta);
    
    while (iRespuesta < 1 || iRespuesta > 5)
    {
        printf("Error, Reingrese entre 1 y 5 \n");
        scanf("%i", &iRespuesta);
    }


    //e) cargue los valores del vector en la fila de la matriz indicada por el usuario

    int num= iRespuesta;
	for (int k=0; k<5; k++)
    {
		Matriz[num - 1][k] = Vector[k];
	}

    //f) muestre el contenido del vector y de la matriz utilizando el while
    printf("\n");
    int i=0;
    int j=0;
    
    while(i < 5)
    { 
     printf("%i \t",Vector[i]);
     i++;
    }
    printf("\n");

    while (i < 5)
    {
        int j=0;
       
       while (j < 5)
      {
        printf("%i \t",Matriz[i][j]);
         j++;
        }
     i++;
     printf("\n");
    }
 

}