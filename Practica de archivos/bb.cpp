#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct cliente
{
    char Nombre[50];
    char Apellido[50];
    char Legajo[10];
};

struct indice
{
    int Posicion;
    char Legajo[10];
};
struct cliente DatosCliente;
struct indice Indice;

void Alta();
int valida(char LegajoAux[10]);
void OrdenarIndice();
void Listar();
void Buscar();

int main()
{
    int opcion = 0;
    int opcion2 = 0;

    do
    {
        cout << "Meñu" << endl;
        cout << "1 - Alta Persona" << endl;
        cout << "2 - Buscar Persona" << endl;
        cout << "3 - Listar Personas" << endl;
        cout << "4 - Ordenar Indice" << endl;
        cout << "5 - Salir" << endl;
        cin >> opcion;
        cout << endl;

        switch (opcion)
        {
        case 1:
            Alta();
            break;

        case 2:
            Buscar();
            break;

        case 3:
            Listar();
            break;

        case 4:
            OrdenarIndice();
            break;

        case 5:
            cout << "esta seguro que quiere salir?" << endl;
            cout << "1 - Si" << endl;
            cout << "2 - No" << endl;
            cin >> opcion2;
            cout << endl;
            break;

        default:
            cout << "Opcion incorrecta!" << endl;
            return main();
            break;
        }
    } while (opcion != 5);
}

void Alta()
{
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("M1.dat", ios::binary | ios::app | ios::ate);
    int validacion = -1;

    validacion = valida(DatosCliente.Legajo);
    if (validacion == 1)
    {
        cout << "Ya existe la persona" << endl;
    }
    else
    {
        cout << "Ingrese el Nombre: ";
        cin.getline(DatosCliente.Nombre, 50);
        cout << "Ingrese el Apellido: ";
        cin.getline(DatosCliente.Apellido, 50);

        ArchivoMaestro.write((char *)&DatosCliente, sizeof(DatosCliente));

        ofstream ArchivoIndice;
        ArchivoIndice.open("M2.inx", ios::binary | ios::app | ios::ate);
        Indice.Posicion = ArchivoMaestro.tellp();
        Indice.Posicion = Indice.Posicion - sizeof(DatosCliente);
        strcpy(Indice.Legajo, DatosCliente.Legajo);
        ArchivoIndice.write((char *)&Indice, sizeof(Indice));

        ArchivoIndice.close();
        ArchivoMaestro.close();
    }
}

int valida(char LegajoAux[10])
{
    ifstream ArchivoIndice;
    ArchivoIndice.open("M2.inx", ios::binary);
    ArchivoIndice.seekg(0, ios::end);
    int inicio = 0;
    int medio;
    int fin = (ArchivoIndice.tellg() / sizeof(Indice) - 1);

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        ArchivoIndice.seekg(medio * sizeof(Indice));
        ArchivoIndice.read((char *)&Indice, sizeof(Indice));
        if (strcmp(LegajoAux, Indice.Legajo) == 0)
        {
            return 1;
        }
        else
        {
            if (strcmp(LegajoAux, Indice.Legajo) == -1)
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

void OrdenarIndice()
{
    fstream ArchivoIndice;
    ArchivoIndice.open("M2.inx", ios::binary | ios::in | ios::out);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("M1.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int posicion = ArchivoMaestro.tellg();
    int elementos = posicion / sizeof(DatosCliente);
    ArchivoMaestro.close();

    struct indice IndiceAux;

    for (int i = 1; i < elementos; i++)
    {
        for (int j = 0; j < elementos; j++)
        {
            ArchivoIndice.seekg(j * sizeof(Indice), ios::beg);
            ArchivoIndice.read((char *)&IndiceAux, sizeof(Indice));
            ArchivoIndice.read((char *)&Indice, sizeof(Indice));
            if (strcmp(IndiceAux.Legajo, Indice.Legajo) == 1)
            {
                ArchivoIndice.seekp(j * sizeof(Indice));
                ArchivoIndice.write((char *)&Indice, sizeof(Indice));
                ArchivoIndice.write((char *)&IndiceAux, sizeof(Indice));
            }
        }
    }
    ArchivoIndice.close();
}

void Buscar()
{
    char LegajoAux[10];
    cout << "Ingrese el legajo: ";
    cin.getline(LegajoAux, 10);

    ifstream ArchivoIndice;
    ArchivoIndice.open("M2.inx", ios::binary | ios::in);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("M1.dat", ios::binary);
    int inicio = 0;
    int medio;
    int fin = (ArchivoMaestro.tellg() / sizeof(DatosCliente) - 1);
    ArchivoMaestro.close();
    int encontrado = 0;

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        ArchivoIndice.seekg(medio * sizeof(Indice));
        ArchivoIndice.read((char *)&Indice, sizeof(Indice));
        if (strcmp(LegajoAux, Indice.Legajo) == 0)
        {
            ArchivoMaestro.open("M2.dat", ios::binary);
            ArchivoMaestro.seekg(Indice.Posicion);
            ArchivoMaestro.read((char *)&DatosCliente, sizeof(DatosCliente));
            cout << "Legajo: " << DatosCliente.Legajo << endl;
            cout << "Nombre: " << DatosCliente.Nombre << endl;
            cout << "Apellido: " << DatosCliente.Apellido << endl;

            encontrado = 1;
            fin = -1;
            ArchivoIndice.close();
            ArchivoMaestro.close();
        }
        else
        {
            if (strcmp(LegajoAux, Indice.Legajo) == -1)
            {
                fin = medio - 1;
            }
            else
            {
                inicio = medio + 1;
            }
        }
    }
    if (encontrado != 1)
    {
        cout << "Legajo no encontrado!" << endl;
    }
}

void Listar()
{

    ifstream ArchivoIndice;
    ArchivoIndice.open("M2.inx", ios::binary);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("M1.dat", ios::binary);

    cout << "1- Listar Maestro" << endl;
    cout << "2- Listar Indice";
}