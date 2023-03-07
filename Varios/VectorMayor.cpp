#include <iostream>

using namespace std;

int main()
{
    int Vector[100];
    int CantElementos = 0;
    int mayor = 0;

    cout << "Ingrese la cantidad de elementos del vector: ";
    cin >> CantElementos;

    for (int i = 0; i < CantElementos; i++)
    {
        cout << "Ingrese un numero: ";
        cin >> Vector[i];

        if (Vector[i] > mayor)
        {
            mayor = Vector[i];
        }
    }

    for (int i = 0; i < CantElementos; i++)
    {
        cout << "Vector[" << i << "]" << Vector[i] << endl;
    }

    cout << endl;
    cout << "El numero mayor del vector es: " << mayor;

    return 0;
}