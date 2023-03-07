#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void lectura();
void escritura();

int main()
{

    int opcion = 0;

    cout << "Ingrese 1 para escribir en texto" << endl;
    cout << "Ingrese 2 para leer lo escrito";
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        escritura();
        break;

    case 2:
        lectura();
        break;

    default:
        cout << "Ingrese una opcion correcta";
        return main();
        break;
    }

    return 0;
}

void escritura()
{
    string texto;
    ofstream archivoEscritura;
    string nombre;

    cout << "Ingrese el nombre del archivo para guardar datos: ";
    cin >> nombre;
    nombre = nombre + "Datos.dat";

    archivoEscritura.open(nombre, ios::app | ios::binary | ios::ate);

    cout << "Ingrese el texto para el archivo: ";
    getline(cin,texto);

    archivoEscritura.close();
}

void lectura()
{
    ifstream archivoLectura;
    string texto;
    string nombre;

    cout << "Ingrese el nombre del archivo a leer: ";
    cin >> nombre;

    nombre = nombre + "Datos.dat";

    ifstream(nombre, ios::binary);

    if (archivoLectura.fail())
    {
        cout << "Error al intentar abrir el archivo";
        exit(1);
    }

    while (!archivoLectura.eof())
    {
        getline(archivoLectura, texto);
        cout << texto << endl;
    }

    archivoLectura.close();
}

void concatenar();

void concatenar()
{
    ofstream archivo;
    char rubro[10];
    int doc = 4;
    cout << "Ingrese el rubro: ";
    cin >> rubro;

    string nombre;
    nombre += "Productos"; // nombre = nombre + "Productos"
    nombre += rubro;       // nombre = nombre + rubro
    nombre += ".dat";      // nombre = nombre + ".dat"

    nombre = "";
    nombre += "Productos"; // nombre = nombre + "Productos"
    if (doc % 2 == 0)
        nombre += "par.inx";
    else
        nombre += "impar.inx";

    cout << nombre << endl;

    archivo.open(nombre, ios::app | ios::ate);
    archivo.close();
}