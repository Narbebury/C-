/*Programa que defina un vector y calcule la suma de sus elementos*/
#include <iostream>

using namespace std;

int main()
{
    int numeros[5] = {1, 2, 3, 4, 5};
    int suma = 0;

    for (int i = 0; i < 5; i++)
    {
        suma = suma + numeros[i];
    }

    cout << "La suma de los elementos del vector es: " << suma;
    cout << endl;
    // Vector de numeros y calcular la multiplicacion acumulada de sus elementos
    int Vector[5] = {4, 5, 6, 7, 8};
    int multiplicacion = 1;

    for (int i = 0; i < 5; i++)
    {
        multiplicacion = multiplicacion * Vector[i];
    }

    cout << "La multiplicacion de los numeros del vector es: " << multiplicacion;

    return 0;
}