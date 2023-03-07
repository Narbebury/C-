/*Archivos C++ - Posicionamiento --- Ejercicio 1) Personas
Se desea desarrollar un programa para resguardar datos en un archivo binario almacenados en una estructura de Personas. Entre los datos están: Documento, apellido y nombre.
Desarrollar un menú que permita: Cargar, Listar, Mostrar, Buscar y Salir del programa según el usuario lo desee.
Opción Cargar: una vez registrados los datos en el archivo deberá indicarse la posición del registro. Ej: registro guardado en posición: 3
Opción Listar: deberán mostrarse todos los datos de las personas almacenadas en el archivo además de la posición del registro dentro del archivo.
Opción Mostrar: solicitar al usuario el registro (posición) de la persona que desea mostrar por pantalla. De no encontrarse indicar que el registro no existe.
Opción Buscar: solicitar al usuario el Documento de la persona, buscarlo en el archivo y mostrar su posición. De no encontrarse indicar que el documento no existe.
Opción Salir: consultar al usuario si está seguro de querer finalizar el programa.*/
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct persona
{
    char Nombre[50];
    char Apellido[50];
    long long Documento;
};

struct persona Personas;

void Cargar();
void Listar();
void Mostrar();
void Buscar();

int main()
{
    int opcion = 0;
    int op2 = 0;

    do
    {

        cout << "MENU" << endl;
        cout << "1 - Cargar Persona" << endl;
        cout << "2 - Listar Persona" << endl;
        cout << "3 - Mostrar Persona" << endl;
        cout << "4 - Buscar Persona" << endl;
        cout << "5 - Salir" << endl;
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            Cargar();
            break;

        case 2:
            Listar();
            break;

        case 3:
            Mostrar();
            break;

        case 4:
            Buscar();
            break;

        case 5:

            cout << "Esta seguro que quiere salir ?" << endl;
            cout << "1 - Si" << endl;
            cout << "2 - No" << endl;
            cin >> op2;

            if (op2 == 1)
            {
                cout << "Hasta luego...";
            }
            else
            {
                return main();
            }

            break;

        default:
            cout << "Ingrese una opcion correcta" << endl;
            return main();
            break;
        }

    } while (opcion != 5);

    return 0;
}

void Cargar()
{
    ofstream archivoMaestro;
    archivoMaestro.open("Personas.dat", ios::binary | ios::app | ios::ate);

    if (archivoMaestro.fail())
    {
        cout << "Error al abrir el archivo";
        exit(1);
    }

    fflush(stdin);

    cout << "Ingrese el Nombre: ";
    cin.getline(Personas.Nombre, 50);
    cout << endl;
    fflush(stdin);

    cout << "Ingrese el Apellido: ";
    cin.getline(Personas.Apellido, 50);
    cout << endl;
    fflush(stdin);

    cout << "Ingrese el Documento: ";
    cin >> Personas.Documento;
    fflush(stdin);

    archivoMaestro.write((char *)&Personas, sizeof(persona));
    cout << "Posicion: " << archivoMaestro.tellp();
    cout << "Registro: " << archivoMaestro.tellp() / sizeof(Personas);

    archivoMaestro.close();
    cout << endl;
}

void Listar()
{
    ifstream archivoListar;
    archivoListar.open("Personas.dat", ios::binary);

    if (archivoListar.fail())
    {
        cout << "Error al intentar abrir el archivo";
        exit(1);
    }
    //! archivoM.read((char*)  &marcas,sizeof(marcas)).eof()
    while (!archivoListar.read((char *)&Personas, sizeof(persona)).eof())
    {
        cout << "Nombre: " << Personas.Nombre;
        cout << endl;
        cout << "Apellido: " << Personas.Apellido;
        cout << endl;
        cout << "Documento: " << Personas.Documento;
        cout << endl;
        cout << "Posicion: " << archivoListar.tellg();
        cout << endl;
        cout << "Registro: " << archivoListar.tellg() / sizeof(Personas);
        cout << endl;
        cout << "Posicion: " << archivoListar.tellg();
        cout << endl;
        cout << "Registro: " << archivoListar.tellg() / sizeof(Personas);
        cout << endl;
        cout << endl;
    }
    archivoListar.close();
}

void Mostrar()
{
    ifstream archivoMostrar;
    archivoMostrar.open("Personas.dat", ios::binary);

    if (archivoMostrar.fail())
    {
        cout << "Error al abrir el archivo";
        exit(1);
    }

    int Registro = 0;
    cout << "Ingrese el registro de la persona que quiere buscar: ";
    cin >> Registro;
    cout << endl;

    while (!archivoMostrar.read((char *)&Personas, sizeof(persona)).eof())
    {
        if (Registro == archivoMostrar.tellg())
        {
            cout << "Persona encontrada!" << endl;
            cout << "Nombre:" << Personas.Nombre;
            cout << endl;
            cout << "Apellido: " << Personas.Apellido;
            cout << endl;
            cout << "Documento: " << Personas.Documento;
            cout << endl;
            cout << "Posicion: " << archivoMostrar.tellg();
            cout << endl;
            cout << "Registro: " << archivoMostrar.tellg() / sizeof(Personas);
            cout << endl;
            cout << endl;
        }
        else
        {
            int op = 0;
            cout << "Persona no encontrada" << endl;
            cout << "Quiere buscar nuevamente ?" << endl;
            cout << "1 - Si" << endl;
            cout << "2 - No" << endl;
            cin >> op;

            if (op == 1)
            {
                return Mostrar();
            }
            else
            {
                cout << "Hasta luego...";
                exit(1);
            }
        }
    }

    archivoMostrar.close();
}

void Buscar()
{
    ifstream archivoBuscar;
    archivoBuscar.open("Personas.dat", ios::binary);

    if (archivoBuscar.fail())
    {
        cout << "Error al abrir el archivo";
        exit(1);
    }

    long long DocumentoBuscado = 0;

    cout << "Ingrese el documento de la persona a buscar: ";
    cin >> DocumentoBuscado;
    fflush(stdin);
    fflush(stdout);

    while (!archivoBuscar.read((char *)&Personas, sizeof(persona)).eof())
    {
        if (DocumentoBuscado == Personas.Documento)
        {
            cout << "Persona encontrada!" << endl;
            cout << "Nombre:" << Personas.Nombre;
            cout << endl;
            cout << "Apellido: " << Personas.Apellido;
            cout << endl;
            cout << "Documento: " << Personas.Documento;
            cout << endl;
            cout << "Posicion: " << archivoBuscar.tellg();
            cout << endl;
            cout << "Registro: " << archivoBuscar.tellg() / sizeof(Personas);
            cout << endl;
            cout << endl;
        }
        else
        {
            cout << "Persona no encontrada" << endl;
        }
    }
    archivoBuscar.close();
}