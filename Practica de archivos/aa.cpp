#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct Persona
{
    char Nombre[50];
    char Apellido[50];
    long long Cuil;
};

struct indice
{
    int Posicion;
    long long Cuil;
};

struct Persona DatosPersona;
struct indice Indice;

void Alta();
int Valido(long long CuilAux);
void Buscar();
void OrdenarIndice();
void Listar();

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
        cout << "5 - Salir"<<endl;
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
    ArchivoMaestro.open("A1.dat", ios::binary | ios::app | ios::ate);

    int Validacion = -1;

    cout << "Ingrese el Cuil: ";
    cin >> DatosPersona.Cuil;
    fflush(stdin);

    Validacion = Valido(DatosPersona.Cuil);
    if (Validacion == 1)
    {
        cout << "La persona ya esta registrada!" << endl;
    }
    else
    {
        cout << "Ingrese el Nombre: ";
        cin.getline(DatosPersona.Nombre, 50);
        fflush(stdin);
        cout << "Ingrese el Apellido: ";
        cin.getline(DatosPersona.Apellido, 50);
        fflush(stdin);

        ArchivoMaestro.write((char *)&DatosPersona, sizeof(DatosPersona));

        ofstream ArchivoIndice;
        ArchivoIndice.open("A2.inx", ios::binary | ios::app | ios::ate);
        Indice.Posicion = ArchivoMaestro.tellp();
        Indice.Posicion = Indice.Posicion - sizeof(DatosPersona);
        Indice.Cuil = DatosPersona.Cuil;
        ArchivoIndice.write((char *)&Indice, sizeof(Indice));

        ArchivoMaestro.close();
        ArchivoIndice.close();
    }
}

int Valido(long long CuilAux)
{
    ifstream ArchivoIndice;
    ArchivoIndice.open("A2.inx", ios::binary);
    ArchivoIndice.seekg(0, ios::end);
    int inicio = 0;
    int medio;
    int fin = (ArchivoIndice.tellg() / sizeof(Indice) - 1);

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
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
}

void OrdenarIndice()
{
    fstream ArchivoIndice;
    ArchivoIndice.open("A2.inx", ios::binary | ios::in | ios::out);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("A1.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int Elementos = (ArchivoMaestro.tellg() / sizeof(DatosPersona));
    ArchivoMaestro.close();

    struct indice IndiceAux;

    for (int i = 1; i < Elementos; i++)
    {
        for (int j = 0; j < Elementos; j++)
        {
            ArchivoIndice.seekg(j * sizeof(Indice), ios::beg);
            ArchivoIndice.read((char *)&IndiceAux, sizeof(Indice));
            ArchivoIndice.read((char *)&Indice, sizeof(Indice));

            if (IndiceAux.Cuil < Indice.Cuil)
            {
                ArchivoIndice.seekg(j * sizeof(Indice));
                ArchivoIndice.read((char *)&Indice, sizeof(Indice));
                ArchivoIndice.read((char *)&IndiceAux, sizeof(Indice));
            }
        }
    }
    ArchivoIndice.close();
}

void Buscar()
{
    long long CuilAux = 0;
    cout << "Ingrese el Cuil: " << endl;
    cin >> CuilAux;
    fflush(stdin);

    ifstream ArchivoIndice;
    ArchivoIndice.open("A2.inx", ios::binary | ios::in);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("A1.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int encontrado = 0;
    int inicio = 0;
    int medio;
    int fin = (ArchivoMaestro.tellg() / sizeof(DatosPersona)) - 1;
    ArchivoMaestro.close();

    while (inicio <= fin)
    {
        medio = (inicio + fin) / 2;
        ArchivoIndice.seekg(medio * sizeof(Indice));
        ArchivoIndice.read((char *)&Indice, sizeof(Indice));
        if (CuilAux == Indice.Cuil)
        {
            ArchivoMaestro.open("A1.dat", ios::binary);
            ArchivoMaestro.seekg(Indice.Posicion);
            ArchivoMaestro.read((char *)&DatosPersona, sizeof(DatosPersona));

            cout << "Cuil: " << DatosPersona.Cuil << endl;
            cout << "Nombre: " << DatosPersona.Nombre << endl;
            cout << "Apellido: " << DatosPersona.Apellido << endl;

            encontrado =1;
            fin = -1;
            ArchivoIndice.close();
            ArchivoMaestro.close();
        }
        else
        {
            if (CuilAux > Indice.Cuil)
            {
                fin = medio -1;
            }
            else
            {
                inicio = medio +1;
            }
            
        }
        
    }
    if (encontrado != 1)
    {
        cout << "Persona no encontrada!" << endl;
    }
}

void Listar()
{
    int opcion = 0;

    cout << "1 - Listar Indice" << endl;
    cout << "2 - Listar Maestro" << endl;
    cin >> opcion;
    cout << endl;

    if (opcion == 1)
    {
        ifstream ArchivoIndice;
        ArchivoIndice.open("A2.inx", ios::binary);

        while (ArchivoIndice.read((char *)&Indice, sizeof(Indice)))
        {
            if (!ArchivoIndice.eof())
            {
                cout << "Cuil: " << Indice.Cuil << endl;
                cout << "Posicion: " << Indice.Posicion << endl;
            }
        }
        ArchivoIndice.close();
    }
    if (opcion == 2)
    {

        ifstream ArchivoMaestro;
        ArchivoMaestro.open("A1.dat", ios::binary);

        while (ArchivoMaestro.read((char *)&DatosPersona, sizeof(DatosPersona)))
        {
            if (!ArchivoMaestro.eof())
            {
                cout << "Cuil: " << DatosPersona.Cuil << endl;
                cout << "Nombre: " << DatosPersona.Nombre << endl;
                cout << "Apellido: " << DatosPersona.Apellido << endl;
            }
        }
        ArchivoMaestro.close();
    }
    if (opcion != 1 && opcion != 2)
    {
        cout << "Ingrese una opcion correcta!" << endl;
        // return Listar();
    }
}
