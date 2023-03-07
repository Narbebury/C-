/*Programa que almacena datos personales
Se almacenara el nombre, apellido y documento de personas para validar,
buscar, ordenar indices*/
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct personas
{
    char Nombre[100];
    char Apellido[100];
    long long Documento;
};

struct indice
{
    long long Documento;
    int posicion;
};

struct personas DatosPersonas;
struct indice Indice;

void AltaPersona();
int ValidoPersona(long long DocumentoAux);
void BusquedaPersona();
void OrdenarIndice();
void ListarPersonas();

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
    fflush(stdin);

    do
    {
        switch (opcion)
        {
        case 1:
            AltaPersona();
            break;

        case 2:
            BusquedaPersona();
            break;

        case 3:
            ListarPersonas();
            break;

        case 4:
            cout << "Esta seguro que quiere salir?";
            cout << "1 - Si\n2 - No\n";
            cin >> opcion2;
            if (opcion2 == 1)
            {
                cout << "Hasta luego...";
                exit(1);
            }
            else
            {
                return main();
            }

            break;
        default:
            cout << "Ingrese una opcion correcta!" << endl;
            //return main();
            break;
        }
    } while (opcion != 4);

    return 0;
}

void AltaPersona()
{
    int Validacion = -1;
    // Abro el archivo Maestro
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("Personas.dat", ios::binary | ios::app | ios::ate);

    cout << "Ingrese el Documento: ";
    cin >> DatosPersonas.Documento;
    fflush(stdin);

    Validacion = ValidoPersona(DatosPersonas.Documento);

    //Valido la existencia del Documento
    if (Validacion == 1)
    {
        cout << "El documento ya existe";
        cout << endl;
    }
    else
    {
        cout << "Ingrese el Nombre: ";
        cin.getline(DatosPersonas.Nombre, 100);
        fflush(stdin);
        cout << "Ingrese el Apellido: ";
        cin.getline(DatosPersonas.Apellido, 100);
        fflush(stdin);

        // Guardo los datos en el archivo Maestro
        ArchivoMaestro.write((char *)&DatosPersonas, sizeof(DatosPersonas));

        // Abro el archivo de indice, guardo la posicion y luego los documentos
        ofstream ArchivoIndice;
        ArchivoIndice.open("IndicePersonas.inx", ios::binary | ios::app | ios::ate);

        Indice.posicion = ArchivoMaestro.tellp();
        Indice.posicion = Indice.posicion - sizeof(DatosPersonas);
        Indice.Documento = DatosPersonas.Documento;
        ArchivoIndice.write((char *)&Indice, sizeof(Indice));

        ArchivoMaestro.close();
        ArchivoIndice.close();
        OrdenarIndice();
    }
}

// Validacion de documento mediante Busqueda Binaria
int ValidoPersona(long long DocumentoAux)
{
    ifstream ArchivoIndice;
    ArchivoIndice.open("IndicePersonas.inx", ios::binary);
    int medio;
    int inicio = 0;
    ArchivoIndice.seekg(0, ios::end);
    int fin = (ArchivoIndice.tellg() / sizeof(indice) - 1);

    // Comienza el ciclo de la Busqueda Binaria
    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        ArchivoIndice.seekg(medio * sizeof(indice));
        ArchivoIndice.read((char *)&Indice, sizeof(indice));

        if (DocumentoAux == Indice.Documento)
        {
            return 1;
        }
        else
        {
            if (DocumentoAux > Indice.Documento)
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

// Ordeno el indice por metodo burbuja.
void OrdenarIndice()
{

    fstream ArchivoIndice;
    ArchivoIndice.open("IndicePersonas.inx", ios::binary | ios::in | ios::out);

    ifstream archEntrega;
    archEntrega.open("Personas.dat", ios::binary);
    archEntrega.seekg(0, ios::end);

    struct indice IndiceAux;

    int pos = archEntrega.tellg();
    archEntrega.close();

    int Elementos = pos / sizeof(personas);

    for (int i = 1; i < Elementos; i++)
    {
        for (int j = 0; j < Elementos; j++)
        {
            ArchivoIndice.seekg(j * sizeof(Indice), ios::beg);
            ArchivoIndice.read((char *)&IndiceAux, sizeof(Indice));
            ArchivoIndice.read((char *)&Indice, sizeof(Indice));

            if (IndiceAux.Documento < Indice.Documento)
            {
                ArchivoIndice.seekp(j * sizeof(Indice));
                ArchivoIndice.write((char *)&Indice, sizeof(Indice));
                ArchivoIndice.write((char *)&IndiceAux, sizeof(Indice));
            }
        }
    }

    ArchivoIndice.close();
}

void BusquedaPersona()
{
    long long DocumentoAux;

    cout << "Ingrese el Documento a buscar: ";
    cin >> DocumentoAux;
    cout << endl;

    // Busco en indice por Busqueda Binaria.
    ifstream ArchivoIndice;
    ArchivoIndice.open("IndicePersonas.inx", ios::binary | ios::in);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Personas.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);
    int posicion = ArchivoMaestro.tellg();
    int fin = (posicion / sizeof(personas)) - 1;
    ArchivoMaestro.close();

    int n;
    int medio;
    int inicio = 0;
    int encontrado = 0;

    while (inicio <= fin)
    {

        medio = (fin + inicio) / 2;

        // Posiciono en el medio del archivo
        ArchivoIndice.seekg(medio * sizeof(Indice));
        ArchivoIndice.read((char *)&Indice, sizeof(Indice));

        if (Indice.Documento == DocumentoAux)
        {
            // Muestro los datos de las entregas.
            ifstream ArchivoMaestro;
            ArchivoMaestro.open("Entregas.dat", ios::binary);
            ArchivoMaestro.seekg(Indice.posicion);
            ArchivoMaestro.read((char *)&DatosPersonas, sizeof(personas));

            cout << "Documento: " << DatosPersonas.Documento;
            cout << endl;

            cout << "Nombre: " << DatosPersonas.Nombre;
            cout << endl;

            cout << "Apellido: " << DatosPersonas.Apellido;
            cout << endl;
            cout << endl;

            encontrado = 1;
            fin = -1;
        }
        else
        {
            if (DocumentoAux > Indice.Documento)
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

void ListarPersonas()
{
    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Personas.dat", ios::binary);

    while (!ArchivoMaestro.read((char *)&DatosPersonas, sizeof(DatosPersonas)).eof())
    {
        cout << "Nombre: " << DatosPersonas.Nombre;
        cout << endl;
        cout << "Apellido: " << DatosPersonas.Apellido;
        cout << endl;
        cout << "Documento: " << DatosPersonas.Documento;
        cout << endl;
    }
}