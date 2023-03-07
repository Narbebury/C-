#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main()
{

    struct Productos
    {
        int codigo;
        char descripcion[50];
        float precio;
    };

    struct Productos producto;

    // Escritura
    ofstream archivoEscritura;
    archivoEscritura.open("ArchivoGeneral.dat", ios::app | ios::binary);

    producto.codigo = 1;
    strcpy(producto.descripcion, "Mermelada");
    producto.precio = 100.23;

    producto.codigo = 2;
    strcpy(producto.descripcion, "Galletira");
    producto.precio = 45, 44;

    archivoEscritura.write((char *)&producto, sizeof(Productos));
    archivoEscritura.close();

    // Si solo quiero guardar un elemento hago lo siguente:
    // archivoEscritura.write((char*)&producto.descripcion,sizeof(Productos->descripcion));

    // Lectura
    ifstream archivoLectura;
    archivoLectura.open("ArchivoGeneral.dat", ios::binary);

    if (archivoLectura.is_open())
    {
        do
        {
            archivoLectura.read((char *)&producto, sizeof(Productos));

            cout << "Codigo: " << producto.codigo << endl;
            cout << "Producto: " << producto.descripcion << endl;
            cout << "Precio: " << producto.precio << endl;
        } while (!archivoLectura.eof());

        archivoLectura.close();
    }
    else
    {
        cout << "Error al abrir el archivo";
    }
}