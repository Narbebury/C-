#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct persona
{
    long long Cuil;
    char Nombre[100];
    char Apellido[100];
};

struct indice
{
    long long Cuil;
    int posicion;
};

struct persona DatosPersona;
struct indice Indice;

void Alta();
int validacion(long long CuilAux);
void busqueda();
void OrdenoIndice();
void Listar();

int main()
{

    int opcion = 0;
    int opcion2 = 0;

    cout << "Menu" << endl;
    cout << "1 - Alta" << endl;
    cout << "2 - Buscar" << endl;
    cout << "3 - Listar" << endl;
    cout << "4 - Salir" << endl;
    cin >> opcion;
    fflush(stdin);

    do
    {
        switch (opcion)
        {
        case 1:
            Alta();
            break;

        case 2:
            busqueda();

            break;
        case 3:
            Listar();
            break;

        case 4:
            cout << "Esta seguro que quiere salir ?" << endl;
            cout << "1 - Si" << endl;
            cout << "2 - No" << endl;
            cin >> opcion2;
            break;

        default:
            cout << "Ingrese una opcion correcta!" << endl;
            break;
        }
    } while (opcion != 4);
}

void Alta()
{
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("Maestro.dat", ios::binary | ios::app | ios::ate);

    int valido = -1;

    cout << "Ingrese el cuil de la persona ";
    cin >> DatosPersona.Cuil;
    cout << endl;
    fflush(stdin);

    valido = validacion(DatosPersona.Cuil);
    if (valido == 1)
    {
        cout << "La persona ya esta registrada:";
        cout << endl;
    }
    else
    {
        cout << "Ingrese el nombre: ";
        cin.getline(DatosPersona.Nombre, 50);
        fflush(stdin);

        cout << "Ingrese el Apellido: ";
        cin.getline(DatosPersona.Apellido, 50);
        fflush(stdin);

        // Guardo datos en el archivo maestro
        ArchivoMaestro.write((char *)&DatosPersona, sizeof(DatosPersona));

        // Guardo datos en el indice
        ofstream ArchivoIndice;
        ArchivoIndice.open("Indice.inx", ios::binary | ios::app | ios::ate);
        Indice.posicion = ArchivoMaestro.tellp();
        Indice.posicion = Indice.posicion - sizeof(DatosPersona);
        Indice.Cuil = DatosPersona.Cuil;

        ArchivoIndice.write((char *)&Indice, sizeof(Indice));

        ArchivoMaestro.close();
        ArchivoIndice.close();

        OrdenoIndice();
    }
}

int validacion(long long CuilAux)
{
    ifstream ArchivoIndice;
    ArchivoIndice.open("Indice.inx", ios::binary);
    int medio;
    int inicio = 0;
    ArchivoIndice.seekg(0, ios::end);
    int fin = (ArchivoIndice.tellg() / sizeof(indice) - 1);

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        ArchivoIndice.seekg(medio * sizeof(indice));
        ArchivoIndice.read((char *)&Indice, sizeof(indice));

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
                fin = medio + 1;
            }
        }
    }

    ArchivoIndice.close();
    return 0;
}

/*
void busqueda()
{
    cout << "Ingrese el cuil de la persona a buscar:";
    long long CuilAux;
    cin >> CuilAux;
    cout << endl;

    // abro archivo de indices pero voy a posicionarme al principio con el maestro
    ifstream ArchivoIndice;
    ArchivoIndice.open("Indice.inx", ios::binary | ios::in);

    ifstream ArchivoMaestro;
    ArchivoIndice.open("Maestro.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int inicio = 0;
    int medio;
    int fin = (ArchivoMaestro.tellg() / sizeof(persona) - 1);
    ArchivoMaestro.close();
    int encontrado = 0;

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        ArchivoIndice.seekg(medio * sizeof(indice));
        ArchivoIndice.read((char*)&Indice,sizeof(indice));//ver 2 indice

        if (CuilAux == Indice.Cuil)
        {
            ifstream ArchivoMaestro;
            ArchivoMaestro.open("Maestro.dat",ios::binary);
            ArchivoMaestro.seekg(Indice.posicion);
            ArchivoMaestro.read((char*)&DatosPersona,sizeof(persona));

            cout << "Nombre: "<<DatosPersona.Nombre;
            cout << "Apellido: "<<DatosPersona.Apellido;
            cout << "Cuil: " << DatosPersona.Cuil;

            encontrado = 1;
            fin = -1;
        }
        else
        {
            if (CuilAux > Indice.Cuil)
            {
                fin = medio - 1;
            }
            else
            {
                fin = medio + 1;
            }

        }

    }
    if (encontrado != 1)
    {
        cout << "No se encontro el Cuil de la persona";
    }

}
*/

void busqueda()
{
    cout << "Ingrese el cuil de la persona a buscar:";
    long long CuilAux;
    cin >> CuilAux;
    cout << endl;

    // abro archivo de indices pero voy a posicionarme al principio con el maestro
    ifstream ArchivoIndice;
    ArchivoIndice.open("Indice.inx", ios::binary | ios::in);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Maestro.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int medio;
    int inicio = 0;
    int encontrado = 0;
    int fin = (ArchivoMaestro.tellg() / sizeof(persona) - 1);
    ArchivoMaestro.close();

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        ArchivoIndice.seekg(medio * sizeof(indice));
        ArchivoIndice.read((char *)&Indice, sizeof(indice));

        if (CuilAux == Indice.Cuil)
        {
            ArchivoMaestro.open("Maestro.dat", ios::binary);
            ArchivoMaestro.seekg(Indice.posicion);
            ArchivoMaestro.read((char *)&DatosPersona, sizeof(DatosPersona));

            cout << "Nombre: " << DatosPersona.Nombre;
            cout << "Apellido: " << DatosPersona.Apellido;
            cout << "Cuil: " << DatosPersona.Cuil;

            encontrado = 1;
            fin = -1;

            ArchivoMaestro.close();
            ArchivoIndice.close();
        }
        else
        {
            if (CuilAux > Indice.Cuil)
            {
                fin = medio - 1;
            }
            else
            {
                fin = medio + 1;
            }
        }
    }
    if (encontrado != 1)
    {
        cout << "no se encontro el cuil";
    }
}

void OrdenoIndice()
{
    fstream ArchivoIndice;
    ArchivoIndice.open("Indice.inx", ios::binary | ios::in | ios::out);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Maestro.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);

    int Pos = ArchivoMaestro.tellg();
    int Elementos = Pos / sizeof(persona);

    ArchivoMaestro.close();

    struct indice IndiceAuxiliar;

    for (int i = 1; i < Elementos; i++)
    {
        for (int j = 0; j < Elementos; j++)
        {
            ArchivoIndice.seekg(j * sizeof(Indice), ios::beg);
            ArchivoIndice.read((char *)&IndiceAuxiliar, sizeof(Indice));
            ArchivoIndice.read((char *)&Indice, sizeof(Indice));

            if (IndiceAuxiliar.Cuil < Indice.Cuil)
            {
                ArchivoIndice.seekp(j * sizeof(Indice));
                ArchivoIndice.write((char *)&Indice, sizeof(Indice));
                ArchivoIndice.write((char *)&IndiceAuxiliar, sizeof(Indice));
            }
        }
    }
    ArchivoIndice.close();
}

void Listar()
{
    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Maestro.dat", ios::binary);
    ifstream ArchivoIndice;
    ArchivoIndice.open("Indice.inx", ios::binary);

    cout << "Datos del Archivo Maestro: " << endl;
    while (!ArchivoMaestro.read((char *)&DatosPersona, sizeof(DatosPersona)).eof())
    {
        cout << "Nombre: " << DatosPersona.Nombre;
        cout << endl;
        cout << "Apellido: " << DatosPersona.Apellido;
        cout << endl;
        cout << "Cuil: " << DatosPersona.Cuil;
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << "Datos del Archivo de Indices: " << endl;
    while (!ArchivoIndice.read((char *)&Indice, sizeof(Indice)).eof())
    {
        cout << "Cuil: " << Indice.Cuil;
        cout << endl;
    }

    ArchivoIndice.close();
    ArchivoMaestro.close();
}

