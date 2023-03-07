/*new: Reserva el número de bytes solicitado por la declaración
delete: Libera un bloque de bytes reservado con anterioridad.

Ejemplo: Pedir al usuario n calificacion y almacenarlas en un arreglo dinamico*/
#include <iostream>
#include <stdlib.h> //new & delete
#include <conio.h>
using namespace std;

void PerdirNotas();
void MostrarNotas();

int numCalif, *calif;

int main()
{
    PerdirNotas();
    MostrarNotas();

    //libero la memomria del puntero
    delete[] calif;
    return 0;
}

void PedirNotas()
{
    cout << "Digite el numero de calificaciones: ";
    cin >> numCalif;
    cout << endl;

    calif = new int[numCalif]; // creo el arreglo

    for (int i = 0; i < numCalif; i++)
    {
        cout << "Ingrese una nota: ";
        cin >> calif[i];
        cout << endl;
    }
}

void MostrarNotas()
{
    cout << "Mosrando notas del usuario: "<<endl;
    for (int i = 0; i < numCalif; i++)
    {
        cout << calif[i]<<endl;
    }
}
