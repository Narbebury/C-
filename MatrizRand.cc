#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int matriz[5][5];
    srand(time(NULL));

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matriz[i][j] = 10 + rand() % (40);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("[%i]", matriz[i][j]);
        }
        printf("\n");
    }

    int sumaPares =0;
    int sumaImpares=0;
    printf("Matriz Par\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i % 2 == 0)
            {
                sumaPares = sumaPares + matriz[i][j];
            }
            else
            {

                sumaImpares = sumaImpares + matriz[i][j];
            }
        }
    }
    printf("Total Pares: %i", sumaPares);
    printf("\t\tTotal Impares: %i", sumaImpares);

    return 0;
}