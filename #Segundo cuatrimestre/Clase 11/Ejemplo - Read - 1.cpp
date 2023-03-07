#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int matriz[4][4];
void leer();
void mostrar();
main()
{
    leer();   //Lee y muestra por pantalla
    cargar(); //Lee y carga matriz
    mostrar();
}

void leer()
{
    ifstream archivo;
    archivo.open("ej_write.dat");
    string lectura;

    do
    {
        getline(archivo);
        cout << lectura;

    } while (archivo.eof());

    archivo.close();
}

void cargar() //cargo la matriz
{
    ifstream archivo;
    archivo.open("ej_write.dat");
    string lectura;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; i < 4; j++)
        {
            getline(archivo, lectura);
            matriz[i][j] = stoi(lectura);
        }
    }

    do
    {
        getline(archivo);
        cout << lectura;

    } while (archivo.eof());

    archivo.close();
}