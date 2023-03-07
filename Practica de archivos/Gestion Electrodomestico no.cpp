/*Programa Venta de electrodomesticos
se dara de alta un cliente indicando su cuil, si pago o no, validacion */

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct Persona
{
    char Nombre[50];
    char Apellido[50];
    int Edad;
    long long Documento;
    char Domicilio[50];
    char Localidad[50];
    char Producto[50];
    float Precio;
};

struct indx
{
    int posicion;
    long long DocumentoIndx;
};

struct Persona Cliente;
struct indx Indice;

//DEFINO PROTOTIPO DE LAS FUNCIONES A UTILIZAR
void Alta();
int Valida_Alta(long long);
void BuscarCliente();
void Ordenar_Indice();
void listarIndice();
//void ReporteProdImpago();

int main()
{
    int op = 0;
    int op2 = 0;
    int op3 = 0;

    do
    {
        cout << "MENU" << endl;
        cout << "1 - Alta cliente" << endl;
        cout << "2 - Buscar Cliente" << endl;
        cout << "3 - Listar Clientes" << endl;
        cout << "4 - Reporte de productos impagos" << endl;
        cout << "5 - Salir" << endl;
        cin >> op;
        cout << endl;

        switch (op)
        {
        case 1:
            Alta();
            break;

        case 2:
            BuscarCliente();
            break;

        case 3:
            listarIndice();
            break;

        case 4:
            /* code */
            break;

        case 5:
            cout << "Esta seguro que quiere salir?" << endl;
            cout << "1 - Si" << endl;
            cout << "2 - No" << endl;
            cin >> op2;

            if (op2 == 1)
            {
                cout << "Hasta Luego!";
            }
            if (op2 == 2)
            {
                return main();
            }

            break;

        default:

            cout << "Ingrese una opcion correcta" << endl;
            cout << endl;
            return main();

            break;
        }

    } while (op != 5);
}

void Alta()
{
    ofstream archcliente;
    archcliente.open("Clientes.dat", ios::binary | ios::app | ios::ate);

    int valido = -1;

    cout << "Ingrese el Documento del cliente: ";
    cin >> Cliente.Documento;
    cout << endl;
    fflush(stdin);

    valido = Valida_Alta(Cliente.Documento);

    if (valido == 1)
    {
        int op = 0;
        cout << "El documento ingresado ya existe" << endl;
        cout << "Quiere dar de alta otra persona ?" << endl;
        cout << "1 - Si" << endl;
        cout << "2 - No" << endl;

        if (op == 1)
        {
            return Alta();
        }
        else
        {
            cout << "Hasta luego!";
        }

        cout << endl;
    }
    else
    {
        cout << "Ingrese el Nombre: ";
        cin.getline(Cliente.Nombre, 50);
        cout << endl;

        cout << "Ingrese Apellido: ";
        cin.getline(Cliente.Apellido, 50);
        fflush(stdin);

        cout << endl;
        cout << "Edad: ";
        cin >> Cliente.Edad;
        fflush(stdin);

        cout << "Ingrese el Domicilio: ";
        cin.getline(Cliente.Domicilio, 50);
        cout << endl;
        fflush(stdin);

        cout << "Ingrese la Localidad: ";
        cin.getline(Cliente.Localidad, 50);
        cout << endl;
        fflush(stdin);

        cout << "Ingrese el producto: ";
        cin.getline(Cliente.Producto, 50);
        fflush(stdin);

        cout << "Ingrese el precio: ";
        cin >> Cliente.Precio;
        fflush(stdin);

        //GUARDO DATOS EN ARCHIVO MAESTRO
        archcliente.write((char *)&Cliente, sizeof(Cliente)); //--> TELLP para el indice

        //GUARDO DATOS EN INDICE 1(PAR) si el Documento del cliente es par, caso contrario guardo en indice 2.
        ofstream indiceClientes;
        indiceClientes.open("Clientes.inx", ios::binary | ios::app | ios::ate);

        Indice.posicion = archcliente.tellp();
        Indice.posicion = Indice.posicion - sizeof(Cliente);
        Indice.DocumentoIndx = Cliente.Documento;
        indiceClientes.write((char *)&Indice, sizeof(Indice));

        indiceClientes.close();
        archcliente.close();

        Ordenar_Indice();
    }
}

int Valida_Alta(long long DocumentoAux) // ES SECUENCIAL y PIDE BINARIOstruct cliente
{

    ifstream archivoI;
    archivoI.open("Clientes.inx", ios::binary);
    int medio;
    int inicio = 0;
    archivoI.seekg(0, ios::end);
    int fin = (archivoI.tellg() / sizeof(Indice) - 1);

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        archivoI.seekg(medio * sizeof(Indice));
        archivoI.read((char *)&Indice, sizeof(Indice));

        if (Indice.DocumentoIndx == DocumentoAux)
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

    struct indx Aux;

    //ORDENO INDICE PAR - BURBUJA CORRECTO
    fstream archindiceP;
    archindiceP.open("Clientes.inx", ios::binary | ios::in | ios::out);

    ifstream archCliente;
    archCliente.open("Clientes.dat", ios::binary);
    archCliente.seekg(0, ios::end);

    int pos = archCliente.tellg();
    archCliente.close();

    int ielementos = pos / sizeof(Persona);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            archindiceP.seekg(j * sizeof(Indice), ios::beg);
            archindiceP.read((char *)&Aux, sizeof(Indice));
            archindiceP.read((char *)&Indice, sizeof(Indice));

            if (Aux.DocumentoIndx < Indice.DocumentoIndx)
            {
                archindiceP.seekp(j * sizeof(Indice));
                archindiceP.write((char *)&Indice, sizeof(Indice));
                archindiceP.write((char *)&Aux, sizeof(Indice));
            }
        }
    }

    archindiceP.close();
}

void BuscarCliente()
{
    long long DocumentoAuxBuscado = 0;

    cout << "Ingrese el Documento a buscar: ";
    cin >> DocumentoAuxBuscado;
    fflush(stdin);
    cout << endl;

    //BUSCO EN EL INDICE PAR POR BUSQUEDA BINARIA

    ifstream IndxEntregas;
    IndxEntregas.open("Clientes.inx", ios::binary | ios::in);

    ifstream archivoDatos;
    archivoDatos.open("Clientes.dat", ios::binary);
    archivoDatos.seekg(0, ios::end);
    int posicion = archivoDatos.tellg();
    int fin = (posicion / sizeof(Cliente)) - 1;
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

        if (Indice.DocumentoIndx == DocumentoAuxBuscado)
        {
            // Muestro los datos de las entregas.
            ifstream archivoEntregas;
            archivoEntregas.open("Clientes.dat", ios::binary);
            archivoEntregas.seekg(Indice.posicion);
            archivoEntregas.read((char *)&Cliente, sizeof(Cliente));

            cout << "Cliente encontrado!";
            cout << endl;
            cout << "Datos del cliente: ";
            cout << endl;
            cout << "Documento: " << Cliente.Documento;
            cout << endl;
            cout << "Nombre: " << Cliente.Nombre;
            cout << endl;
            cout << "Apellido: " << Cliente.Apellido;
            cout << endl;
            cout << "Edad: " << Cliente.Edad;
            cout << endl;
            cout << "Domicilio: " << Cliente.Domicilio;
            cout << endl;
            cout << "Localidad: " << Cliente.Localidad;
            cout << endl;
            cout << "Producto: " << Cliente.Producto;
            cout << endl;
            cout << "Precio: $" << Cliente.Precio;
            cout << endl;
            cout << endl;

            encontrado = 1;
            fin = -1;
        }
        else
        {
            if (DocumentoAuxBuscado > Indice.DocumentoIndx)
                fin = medio - 1;
            else
                inicio = medio + 1;
        }
    }
    if (encontrado != 1)
    {
        cout << "No se encontro el Documento buscado!" << endl;
        int op = 0;
        cout << "Quiere buscar otro cliente ? " << endl;
        cout << "1 - Si" << endl;
        cout << "2 - No" << endl;
        cin >> op;
        if (op == 1)
        {
            return BuscarCliente();
        }
        else
        {
            cout << "Hasta luego!";
            abort;
        }
    }
    IndxEntregas.close();
}

void listarIndice()
{

    ifstream archivo;
    archivo.open("Clientes.dat", ios::binary);
    int i = 1;

    while (archivo.read((char *)&Cliente, sizeof(Cliente)))
    {
        if (!archivo.eof())
        {
            cout << "Cliente "<<i++;
            cout << endl;
            cout << "Documento: " << Cliente.Documento;
            cout << endl;
            cout << "Nombre: " << Cliente.Nombre;
            cout << endl;
            cout << "Apellido: " << Cliente.Apellido;
            cout << endl;
            cout << "Edad: " << Cliente.Edad;
            cout << endl;
            cout << "Domicilio: " << Cliente.Domicilio;
            cout << endl;
            cout << "Localidad: " << Cliente.Localidad;
            cout << endl;
            cout << "Producto: " << Cliente.Producto;
            cout << endl;
            cout << "Precio: $" << Cliente.Precio;
            cout << endl;
            cout << endl;
            
        }
    }
    archivo.close();
}
