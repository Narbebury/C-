//Solicite al usuario 2 edades y detemrine cual es la mayor
#include <iostream>
using namespace std;

int main()
{
    int Edad1;
    int Edad2;

    cout << "Ingrese la primer edad: ";
    cin >> Edad1;
    cout << endl;

    cout << "Ingrese la segunda edad ";
    cin >> Edad2;

    if (Edad2 > Edad1)
        cout << "La segunda edad es mayor " << Edad2;
    else
    {
        cout << "La primera edad es mayor o son iguales" << Edad1;
    }
}