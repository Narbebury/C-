/*Solicitar al usuario un tamaño para la definicion de 2 arreglos.
Se leerán datos en dichos arreglos y se obtendrá la suma de los elementos que contiene cada uno de ellos.
Debe mostrarse como resultado la mayor suma */
#include <iostream>

using namespace std;

int main()
{
    int t = 0;
    int SumaA = 0;
    int SumaB = 0;

    cout << "Ingrese la dimencion del arreglo: ";
    cin >> t;

    int *A, *B;
    A = new int[t];
    B = new int[t];

    for (int i = 0; i < t; i++)
    {
        cout << "Ingrese un valor para A[" << i << "]";
        cin >> A[i];
        SumaA += A[i];
    }
    
    for (int i = 0; i < t; i++)
    {
        cout << "Ingrese un valor para B[" << i << "]";
        cin >> B[i];
        SumaB += B[i];
    }

    if (SumaA > SumaB)
    {
        cout<<"La suma de los elementos del Vector A es mayor";
    }
    else if(SumaB > SumaA)
    {
        cout<<"La suma de los elementos del Vector B es mayor";
    }
    else
    {
        cout<<"La suma de los elementos de los 2 vectores es igual";
    }
    

    return 0;
}