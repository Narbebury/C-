/*  Archivos C++ - Índices y Búsquedas: Gestión de Stock de productos
Se desea desarrollar un programa para gestionar un stock de productos.
De cada artículo se cuenta con la siguiente información: código (Alpha), Descripcion (Alpha),
stock (Entero), PuntoReposicion (Entero)
El programa deberá permitir manejar los artículos desde un menú de aplicación.
Se deberán utiliza un archivo de índices que será generado a demanda por el usuario o bien cuando se agreguen 5
artículos al archivo de productos.
*Desarrollar un menú que permita: Alta Producto, Buscar Producto, Listar Reposición, Alta stock, Generar índice y
Salir del programa según el usuario lo desee.
-*validar que no exista*Opción Alta Producto: Registrar los datos del artículo y lo almacena en el archivo productos.dat.
Debe validarse que NO exista el código de producto previamente.
-Opción Buscar Producto: Mostrar por pantalla los datos del artículo ingresando su Código.
-Opción Listar Reposición: Listar TODOS los productos que alcancen el punto de reposición (stock <= PuntoReposición).
-*validar que si exista*Opción Alta Stock: Permitir el ingreso de productos al Stock solicitando el Código de producto y la
cantidad a ingresar. Mostrar los datos del producto con el stock actualizado.Se
deberá validar la existencia del Producto.
Opción Generar Índice: se deberá regenerar el índice de artículos.
Opción Salir: consultar al usuario si está seguro de querer finalizar el programa. */
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct producto
{
    char codigo[10];
    char Descripcion[10];
    int Stock;
    int PuntoReposicion;
};

struct indice
{
    char Codigo[10];
    int posicion;
};

struct producto Productos;
struct indice Indice;

void Alta();
int valida(char CodigoAux[10]);
void BuscarProducto();

int ContadorAltas = 0;

int main()
{
    int opcion = 0;
    int opcion2 = 0;
    asdasd();
    do
    {

        cout << "MENU" << endl;
        cout << "1 - Alta Producto" << endl;
        cout << "2 - Buscar Producto" << endl;
        cout << "3 - Listar Reposicion" << endl;
        cout << "4 - Alta Stock" << endl;
        cout << "5 - Generar indice" << endl;
        cout << "6 - Salir" << endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            Alta();
            break;

        case 2:
            BuscarProducto();
            break;

        case 5:
            cout << "Esta seguro que quiere salir?";
            cout << "1 - Si" << endl;
            cout << "2 - No" << endl;
            cin >> opcion2;
            cout << endl;
            break;
        default:
            cout << "Ingrese una opcion valida" << endl;
            return main();
            break;
        }
    } while (opcion != 6);
}

void Alta()
{
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("Productos.dat", ios::binary | ios::ate | ios::app);
    int validacion = -1;

    validacion = valida(Productos.codigo);

    if (validacion == 1)
    {
        cout << "El codigo ingresado ya existe!" << endl;
    }
    else
    {
        cout << "Ingrese el producto: ";
        cin.getline(Productos.Descripcion, 10);
        fflush(stdin);
        cout << "Ingrese el stock: ";
        cin >> Productos.Stock;
        cout << endl;
        cout << "Ingrese el Punto de Reposicion: ";
        cin >> Productos.PuntoReposicion;
        cout << endl;
        fflush(stdin);

        // Guardo datos en archivo maestro
        ArchivoMaestro.write((char *)&Productos, sizeof(Productos));
        ContadorAltas++;
        if (ContadorAltas >= 5)
        {
            ofstream ArchivoIndice;
            ArchivoIndice.open("Productos.inx", ios::binary | ios::ate | ios::app);

            Indice.posicion = ArchivoMaestro.tellp();
            Indice.posicion = Indice.posicion - sizeof(Productos);
            strcpy(Indice.Codigo, Productos.codigo);
            ArchivoIndice.write((char *)&Indice, sizeof(Indice));
            ArchivoIndice.close();
        }
        ArchivoMaestro.close();
    }
}

int valida(char CodigoAux[10])
{
    ifstream ArchivoIndice;
    ArchivoIndice.open("Productos.inx", ios::binary);
    ArchivoIndice.seekg(0, ios::end);
    int inicio = 0;
    int medio;
    int fin = (ArchivoIndice.tellg() / sizeof(Indice) - 1);

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        ArchivoIndice.seekg(medio * sizeof(Indice));
        ArchivoIndice.read((char *)&Indice, sizeof(Indice));
        if (strcmp(CodigoAux, Indice.Codigo) == 0)
        {
            return 1;
        }
        else
        {
            if (strcmp(CodigoAux, Indice.Codigo) == -1)
            {
                fin = medio - 1;
            }
            else
            {
                inicio = medio + 1;
            }
        }
    }
    ArchivoIndice.close();
    return 0;
}

void BuscarProducto()
{
    char CodigoAux[10];
    cout << "Ingrese el codigo: ";
    cin >> CodigoAux;
    cout << endl;

    ifstream ArchivoIndice;
    ArchivoIndice.open("Productos.inx", ios::binary | ios::in);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Productos.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int encontrado = 0;
    int inicio = 0;
    int medio;
    int fin = (ArchivoMaestro.tellg() / sizeof(Productos) - 1);
    ArchivoMaestro.close();

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        ArchivoIndice.seekg(medio * sizeof(Indice));
        ArchivoIndice.read((char *)&Indice, sizeof(Indice));
        if (strcmp(CodigoAux, Indice.Codigo) == 0)
        {
            ArchivoMaestro.open("Productos.dat", ios::binary);
            ArchivoMaestro.seekg(Indice.posicion);
            ArchivoMaestro.read((char *)&Productos, sizeof(Productos));

            cout << "Producto: " << Productos.Descripcion << endl;
            cout << "Stock: " << Productos.Stock << endl;
            cout << "Punto de reposicion: " << Productos.PuntoReposicion << endl;
            cout << endl;
            cout << endl;

            encontrado = 1;
            fin = -1;

            ArchivoIndice.close();
            ArchivoMaestro.close();
        }
    }
    if (encontrado != 1)
    {
        cout << "No se encontro el producto!" << endl;
    }
}

void asdasd()
{
    int lista[10] = {5, 6, 7, 8, 9, 2, 1, 4, 3, 0};
    int aux = 0;
    int elementos = 10;

    for (int i = 1; i < elementos; i++)
    {
        for (int j = 0; j < elementos - i; j++)
        {
            if (lista[j] > lista[j + 1])
            {
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }

    for (int i = 0; i < elementos; i++)
    {
        cout <<""<<lista[i]<<endl;
    }
    
}