/*Programa de compras en tienda de internet
El siguente programa va a dar de alta a un cliente por medio de su dni, aplicando descuentos si lleva mas de 4 productos.
El programa contara con:
Un menu de alta de cliente, para registrar al nuevo cliente al momento de comprar, validación del mismo mediante su documento, Busqueda del cliente y opcion de salida*/
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/*Defino las estructuras a usar*/

struct cliente
{
    char Nombre[40];
    char Apellido[40];
    long long Documento;
    char Domicilio[40];
    char Producto[40];
    int cantidad;
    float Precio;
};

struct indx
{
    int posicion;
    long long DocumentoIndx;
};

struct cliente Datos_Cliente;
struct indx Indice;

/*Defino prototipos de las funciones a usar:*/
void Alta_Cliente();
int Valida(long long DocumentoAux);
void Buscar_Cliente();
void Ordenar_Indice();
void Listar();

int main()
{
    int opcion = 0;
    int opcion2 = 0;

    cout << "Menu" << endl;
    cout << "1 - Alta Cliente" << endl;
    cout << "2 - Buscar Cliente" << endl;
    cout << "3 - Listar Clientes" << endl;
    cout << "4 - Salir" << endl;
    cin >> opcion;
    
    do
    {
        switch (opcion)
        {
        case 1:
            Alta_Cliente();
            break;

        case 2:
            Buscar_Cliente();
            break;

        case 3:
            Listar();
            break;

        case 4:

            cout << "Esta seguro que quiere salir ?" << endl;
            cout << "1 - Si \n2 - No" << endl;
            cin >> opcion2;
            cout << endl;

            if (opcion2 == 1)
            {
                cout << "Hasta Luego...";
            }
            else
            {
                cout << endl;
                return main();
            }

            break;

        default:
            cout << "Ingrese una opcion correcta!" << endl;
            return main();

            break;
        }

    } while (opcion != 4);
}

void Alta_Cliente()
{

    ofstream archivoMaestro;
    archivoMaestro.open("ClientesTienda.dat", ios::binary | ios::app | ios::ate);

    cout << "Ingrese el Documento del cliente: ";
    cin >> Datos_Cliente.Documento;
    fflush(stdin);
    int valido = -1;

    

    valido = Valida(Datos_Cliente.Documento);

    if (valido == 1)
    {
        int op = 0;
        cout << "El Documento ingresado ya existe" << endl;
        cout << "Quiere ingresar a otra persona ?" << endl;
        cout << "1 - Si" << endl;
        cout << "2 - No" << endl;
        cin >> op;
        fflush(stdin);
        cout << endl;
    
        if (op == 1)
        {
            return Alta_Cliente();
        }
        else
        {
            cout << "Hasta luego!";
        }
    }
    else
    {
        cout << "Ingrese el Nombre: ";
        cin.getline(Datos_Cliente.Nombre, 50);

        cout << "Ingrese Apellido: ";
        cin.getline(Datos_Cliente.Apellido, 50);
        fflush(stdin);

        cout << "Ingrese el Domicilio: ";
        cin.getline(Datos_Cliente.Domicilio, 50);
        fflush(stdin);

        cout << "Ingrese el producto: ";
        cin.getline(Datos_Cliente.Producto, 50);
        fflush(stdin);

        cout << "Ingrese la cantidad: ";
        cin >> Datos_Cliente.cantidad;

        cout << "Ingrese el precio: ";
        cin >> Datos_Cliente.Precio;
        fflush(stdin);

        // Si el cliente lleva mas de 4 productos se aplicará el 20% de descuento
        if (Datos_Cliente.cantidad > 4)
        {
            Datos_Cliente.Precio = Datos_Cliente.Precio * 0.20;
        }

        // GUARDO DATOS EN ARCHIVO MAESTRO
        archivoMaestro.write((char *)&Datos_Cliente, sizeof(cliente));
        

        // GUARDO DATOS EN INDICE
        ofstream IndiceClientes;
        IndiceClientes.open("ClientesTienda.inx", ios::binary | ios::app | ios::ate);

        Indice.posicion = archivoMaestro.tellp();
        Indice.posicion = Indice.posicion - sizeof(Datos_Cliente);
        Indice.DocumentoIndx = Datos_Cliente.Documento;
        IndiceClientes.write((char *)&Indice, sizeof(Indice));

        IndiceClientes.close();
        archivoMaestro.close();

        Ordenar_Indice();
        exit (1);
    }
}

/*Valido al cliente usando el metodo de busqueda binario*/
int Valida(long long DocumentoAux)
{
    ifstream archivoI;
    archivoI.open("ClientesTienda.inx", ios::binary);
    int medio;
    int inicio = 0;
    archivoI.seekg(0, ios::end);
    int fin = (archivoI.tellg() / sizeof(indx) - 1);

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        archivoI.seekg(medio * sizeof(indx));
        archivoI.read((char *)&Indice, sizeof(indx));

        if (DocumentoAux == Indice.DocumentoIndx)
        {
            return 1;
        }
        else
        {
            if (Indice.DocumentoIndx < DocumentoAux)
            {
                fin = medio - 1;
            }
            else
            {
                inicio = medio + 1;
            }
        }
    }
    archivoI.close();
    return 0;
}

void Ordenar_Indice()
{
    // Ordeno el indice por metodo burbuja.
    fstream ArchivoIndex;
    ArchivoIndex.open("ClientesTienda.inx", ios::binary | ios::in | ios::out);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("ClientesTienda.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);

    struct indx IAuxiliar;

    int pos = ArchivoMaestro.tellg();
    ArchivoMaestro.close();

    int ielementos = pos / sizeof(cliente);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            ArchivoIndex.seekg(j * sizeof(Indice), ios::beg);
            ArchivoIndex.read((char *)&IAuxiliar, sizeof(Indice));
            ArchivoIndex.read((char *)&Indice, sizeof(Indice));

            if (IAuxiliar.DocumentoIndx < Indice.DocumentoIndx)
            {
                ArchivoIndex.seekp(j * sizeof(Indice));
                ArchivoIndex.write((char *)&Indice, sizeof(Indice));
                ArchivoIndex.write((char *)&IAuxiliar, sizeof(Indice));
            }
        }
    }

    ArchivoIndex.close();
}

void Buscar_Cliente()
{
    long long DocumentoAux;

    cout << "Ingrese el Documento del Cliente a buscar: ";
    cin >> DocumentoAux;
    cout << endl;

    // Busco en indice por Busqueda Binaria.
    ifstream IndxEntregas;
    IndxEntregas.open("ClientesTienda.inx", ios::binary | ios::in);

    ifstream archivoDatos;
    archivoDatos.open("ClientesTienda.dat", ios::binary);
    archivoDatos.seekg(0, ios::end);
    int posicion = archivoDatos.tellg();
    int fin = (posicion / sizeof(Datos_Cliente)) - 1;
    archivoDatos.close();

    int medio;
    int inicio = 0;
    int encontrado = 0;

    while (inicio <= fin)
    {

        medio = (fin + inicio) / 2;

        // Posiciono en el medio del archivo
        IndxEntregas.seekg(medio * sizeof(Indice));
        IndxEntregas.read((char *)&Indice, sizeof(Indice));

        if (Indice.DocumentoIndx == DocumentoAux)
        {
            // Muestro los datos de las entregas.
            ifstream archivoEntregas;
            archivoEntregas.open("ClientesTienda.dat", ios::binary);
            archivoEntregas.seekg(Indice.posicion);
            archivoEntregas.read((char *)&Datos_Cliente, sizeof(Datos_Cliente));

            cout << "" << Datos_Cliente.Nombre << "||" << Datos_Cliente.Apellido << endl;
            cout << "Documento: " << Datos_Cliente.Documento << endl;
            cout << "Domicilio: " << Datos_Cliente.Domicilio << endl;
            cout << "Producto: " << Datos_Cliente.Producto << endl;
            cout << "Precio: " << Datos_Cliente.Precio << endl;
            cout << "Cantidad: " << Datos_Cliente.cantidad << endl;

            encontrado = 1;
            fin = -1;
        }
        else
        {
            if (DocumentoAux > Indice.DocumentoIndx)
                fin = medio - 1;
            else
                inicio = medio + 1;
        }
    }
    if (encontrado != 1)
    {
        cout << "No se encontro el Documento buscado" << endl;
    }
}

void Listar()
{
    ifstream ArchivoMaestro;

    while (!ArchivoMaestro.read((char *)&Datos_Cliente, sizeof(cliente)).eof())
    {

        cout << "" << Datos_Cliente.Nombre << "||" << Datos_Cliente.Apellido << endl;
        cout << "Documento: " << Datos_Cliente.Documento << endl;
        cout << "Domicilio: " << Datos_Cliente.Domicilio << endl;
        cout << "Producto: " << Datos_Cliente.Producto << endl;
        cout << "Precio: " << Datos_Cliente.Precio << endl;
        cout << "Cantidad: " << Datos_Cliente.cantidad << endl;

    }
    ArchivoMaestro.close();
}
