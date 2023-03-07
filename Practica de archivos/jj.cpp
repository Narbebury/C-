#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// defino estructuras a usar
struct persona
{
    char Nombre[50];
    char Apellido[50];
    long long Cuil;
};

struct indice
{
    long long Cuil;
    int posicion;
};

struct persona DatosPersona;
struct indice Indice;

// defino los prototipos de funciones
void Alta();
int Valida(long long CuilAux);
void OrdenoIndice();
void Buscar();
void ListarIndice();

int main()
{
    int opcion = 0;
    // int opcion2 = 0;

    do
    {
        cout << "Menu" << endl;
        cout << "1 - Alta" << endl;
        cout << "2 - Buscar" << endl;
        cout << "3 - Listar" << endl;
        cout << "4 - Salir" << endl;
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
            ListarIndice();
            break;

        case 4:
            return 1;
            break;

        default:
            cout << "Ingrese una opcion correcta!" << endl;
            cout << endl;
            break;
        }
    } while (opcion != 4);

    return 0;
}

void Alta()
{
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("Maestro1.dat", ios::binary | ios::app | ios::ate);

    cout << "Ingrese el Cuil: ";
    cin >> DatosPersona.Cuil;
    fflush(stdin);

    int validacion = -1;

    validacion = Valida(DatosPersona.Cuil);

    if (validacion == 1)
    {
        cout << "La persona ya esta cargada";
        cout << endl;
    }
    else
    {
        cout << "Ingrese el nombre: ";
        cin.getline(DatosPersona.Nombre, 50);
        fflush(stdin);
        cout << "Ingrese el apellido: ";
        cin.getline(DatosPersona.Apellido, 50);
        fflush(stdin);
        // Guardo datos en archivo maestro
        ArchivoMaestro.write((char *)&DatosPersona, sizeof(DatosPersona));

        // Guardo datos en archivo Indice
        ofstream ArchivoIndice;
        ArchivoIndice.open("Indice1.inx", ios::binary | ios::app | ios::ate);

        Indice.posicion = ArchivoMaestro.tellp();
        Indice.posicion = Indice.posicion - sizeof(DatosPersona);
        Indice.Cuil = DatosPersona.Cuil;
        ArchivoIndice.write((char *)&Indice, sizeof(Indice));

        ArchivoIndice.close();
        ArchivoMaestro.close();

        OrdenoIndice();
    }
}

int Valida(long long CuilAux)
{
    ifstream ArchivoIndice;
    ArchivoIndice.open("Indice1.inx", ios::binary);
    ArchivoIndice.seekg(0, ios::end);

    int medio;
    int inicio = 0;
    int fin = (ArchivoIndice.tellg() / sizeof(Indice) - 1);

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        ArchivoIndice.seekg(medio * sizeof(Indice));
        ArchivoIndice.read((char *)&Indice, sizeof(Indice));
        if (CuilAux == Indice.Cuil)
        {
            return 1;
        }
        else
        {
            if (CuilAux > Indice.Cuil)
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

void OrdenoIndice()
{
    fstream ArchivoIndice;
    ArchivoIndice.open("Indice1.inx", ios::binary | ios::in | ios::out);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Maestro1.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int pos = ArchivoMaestro.tellg();
    int elementos = (pos / sizeof(DatosPersona));
    ArchivoMaestro.close();

    struct indice IndiceAux;

    for (int i = 1; i < elementos; i++)
    {
        for (int j = 0; j < elementos; j++)
        {
            ArchivoIndice.seekg(j * sizeof(Indice), ios::beg);
            ArchivoIndice.read((char *)&IndiceAux, sizeof(Indice));
            ArchivoIndice.read((char *)&Indice, sizeof(Indice));

            if (IndiceAux.Cuil < Indice.Cuil)
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
    long long CuilAux = 0;
    cout << "Ingrese el cuil: ";
    cin >> CuilAux;
    cout << endl;
    fflush(stdin);

    ifstream ArchivoIndice;
    ArchivoIndice.open("Indice1.inx", ios::binary | ios::in);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Maestro1.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int inicio = 0;
    int medio;
    int pos = ArchivoMaestro.tellg();
    int fin = (pos / sizeof(DatosPersona)) - 1;
    int encontrado = 0;
    ArchivoMaestro.close();

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;

        ArchivoIndice.seekg(medio * sizeof(Indice));
        ArchivoIndice.read((char *)&Indice, sizeof(Indice));

        if (CuilAux == DatosPersona.Cuil)
        {
            ifstream ArchivoMaestro;
            ArchivoMaestro.open("Maestro1.dat", ios::binary);
            ArchivoMaestro.seekg(Indice.posicion);
            ArchivoMaestro.read((char *)&DatosPersona, sizeof(DatosPersona));
            cout << endl;
            cout << "Cuil: " << DatosPersona.Cuil << endl;
            cout << "Nombre: " << DatosPersona.Nombre << endl;
            cout << "Apellido: " << DatosPersona.Apellido << endl;
            cout << endl;

            encontrado = 1;
            fin = -1;
            // ArchivoIndice.close();
            // ArchivoMaestro.close();
        }
        else
        {
            if (CuilAux > Indice.Cuil)
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
        cout << "Cuil no encontrado!" << endl;
    }
}

void ListarIndice()
{
    ifstream ArchivoIndice;
    ArchivoIndice.open("Indice1.inx", ios::binary);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Maestro1.dat", ios::binary);

    while (ArchivoIndice.read((char *)&Indice, sizeof(Indice)))
    {
        if (!ArchivoIndice.eof())
        {
            cout << "Cuil: " << Indice.Cuil << endl;
        }
    }

    cout << "LISTO MAESTRO: " << endl;
    while (ArchivoMaestro.read((char *)&DatosPersona, sizeof(DatosPersona)))
    {
        if (!ArchivoMaestro.eof())
        {
            cout << "Cuil: " << DatosPersona.Cuil << endl;
        }
    }

    ArchivoIndice.close();

    ArchivoMaestro.close();
}