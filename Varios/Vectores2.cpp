/*Programa que lea numeros de un vector y muestre el indice*/
#include <iostream>

using namespace std;

int main()
{
        int numeros[100];
        int n = 0;

        cout << "Digite el numero de elementos que va a tener el arreglo: ";
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cout << "Digite un numero: ";
            cin >> numeros[i];
        }

        for (int i = 0; i < n; i++)
        {
            cout<<"Vector["<<i<<"]: "<<numeros[i]<<endl;
        }
    
    // Defino un vector de numeros y muestro en la salida el orden inverso
    int vector2[100];
    int CantNum = 0;

    cout << "Digite el numero de elementos que va a tener el arreglo: ";
    cin >> CantNum;
    fflush(stdin);
    fflush(stdout);

    for (int i = 0; i < CantNum; i++)
    {
        cout << "Digite un numero: ";
        cin >> vector2[i];
    }

    for (int i = CantNum - 1; i >= 0; i--)
    {
        cout << "Vector[" << i << "]: " << vector2[i] << endl;
    }

     return 0;
}