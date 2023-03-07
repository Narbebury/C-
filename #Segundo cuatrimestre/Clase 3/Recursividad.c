#include <stdio.h>
int rFactorial(int);
int iFactorial(int);

int resultado = 0;

main()
{
    printf("%i \n", rFactorial(3));
}

int rFactorial(int n)
{

    printf("Res: %i \n", resultado);
    printf("Num: %i \n", n);


    if (n == 0)
        return 1;
    else
    {
        resultado = rFactorial(n-1) * n;

        return resultado;
    }



}
