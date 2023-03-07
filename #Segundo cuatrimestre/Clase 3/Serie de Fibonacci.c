#include <stdio.h>
// int rFactorial(int);


int fibonacci (int n)
{
    if(n <= 1) return n; //Condicion base
    else
    {
        return fibonacci(n-1)+fibonacci(n-2); //Condicion recursiba
    }
    
}