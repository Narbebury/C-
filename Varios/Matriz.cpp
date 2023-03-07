#include <iostream>

using namespace std;

int main()
{
    int numeros[100][100], filas, columnas;

    cout << "Ingrese el numero de filas: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas: ";
    cin >> columnas;

    // almaceno
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            cout << "Ingrese el numero para [" << i << "][" << j << "] ";
            cin >> numeros[i][j];
        }
    }

    // muestro
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            cout << numeros[i][j];
        }
        cout << endl;
    }

    int num[100][100],fil,col;
    cout << "Digite el numero de filas: ";
    cin >> fil;
    cout << "Digite el numero de columnas: ";
    cin >> col;

    for (int i = 0; i < fil; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << "Digite un numero [" << i << "][" << j << "]: ";
            cin >> numeros[i][j];
        }
    }

    cout << "\n\nMostrando diagonal principal de la matriz\n";
    for (int i = 0; i < fil; i++)
    {
        for (int j = 0; j < col; j++)
        {

            if (i == j)
            {
                cout << numeros[i][j];
            }
            else
                cout << " ";
        }
        cout << "\n";
    }
}