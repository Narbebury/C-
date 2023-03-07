/*Programa para almacenar datos de los alumnos de una universidad*/
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct Persona
{
    char Nombre[100];
    char Apellido[100];
    int Edad;
    float Nota;
    int Legajo;
    char Materia[50];
};

struct indice
{
    int Legajo;
    int Posicion;
};

struct Persona DatosAlumno;
struct indice IndiceAlumno;

void AltaAlumno();
int ValidoAlumno(int legajo);
void OrdenamientoIndice();
void BuscarAlumno();
void ListarAlumnos();
void BuscarAlumno();

int main()
{
    int opcion = 0;
    // int opcion2 = 0;

    cout << "MENU" << endl;
    cout << "1 - Alta Alumno" << endl;
    cout << "2 - Buscar Alumno" << endl;
    cout << "3 - Listar Alumnos" << endl;
    cout << "4 - Salir" << endl;
    cin >> opcion;

    do
    {
        switch (opcion)
        {
        case 1:
            AltaAlumno();
            break;

        case 2:
            BuscarAlumno();
            break;

        case 3:
            ListarAlumnos();
            break;

        case 4:
            return 1;
            break;

        default:
            cout << "Opcion incorrecta!" << endl;
            return main();
            break;
        }

    } while (opcion != 5);

    return 0;
}

void AltaAlumno()
{
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("Alumnos.dat", ios::binary | ios::app | ios::ate);

    if (ArchivoMaestro.fail())
    {
        cout << "Error al abrir el archivo";
        exit(1);
    }

    int validacion = -1;

    cout << "Ingrese el legajo del alumno: ";
    cin >> DatosAlumno.Legajo;
    cout << endl;
    fflush(stdin);
    validacion = ValidoAlumno(DatosAlumno.Legajo);

    if (validacion == 1)
    {
        int op = 0;
        cout << "El Legajo ingresado ya existe" << endl;
        cout << "Quiere ingresar otro ?" << endl;
        cout << "1 - Si" << endl;
        cout << "2 - No" << endl;
        cin >> op;
        fflush(stdin);
        cout << endl;

        if (op == 1)
        {
            return AltaAlumno();
        }
        else
        {
            cout << "Hasta luego!";
            exit(1);
        }
    }
    else
    {

        cout << "Ingrese el nombre: ";
        cin.getline(DatosAlumno.Nombre, 100);
        fflush(stdin);
        cout << "Ingrese el apellido: ";
        cin.getline(DatosAlumno.Apellido, 100);
        fflush(stdin);
        cout << "Ingrese la edad: ";
        cin >> DatosAlumno.Edad;
        cout << endl;
        fflush(stdin);
        cout << "Ingrese la materia: ";
        cin.getline(DatosAlumno.Materia, 50);
        fflush(stdin);
        cout << "Ingrese la nota: ";
        cin >> DatosAlumno.Nota;
        fflush(stdin);

        // Guardo datos en archivo Maestro
        ArchivoMaestro.write((char *)&DatosAlumno, sizeof(Persona));

        // Guardo datos en mi indice
        ofstream ArchivoIndice;
        ArchivoIndice.open("AIndice.inx", ios::binary | ios::app | ios::ate);

        IndiceAlumno.Posicion = ArchivoIndice.tellp();
        IndiceAlumno.Posicion = IndiceAlumno.Posicion - sizeof(DatosAlumno);
        IndiceAlumno.Legajo = DatosAlumno.Legajo;

        ArchivoMaestro.close();
        ArchivoIndice.close();
        
        OrdenamientoIndice();

    }
}

// Realizo la validación mediante la busqueda binaria
int ValidoAlumno(int legajo)
{
    ifstream ArchivoAlumIndice;
    ArchivoAlumIndice.open("AIndice.inx", ios::binary);
    int medio;
    int inicio = 0;
    ArchivoAlumIndice.seekg(0, ios::end);
    int fin = (ArchivoAlumIndice.tellg() / sizeof(indice) - 1);

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        ArchivoAlumIndice.seekg(medio * sizeof(indice));
        ArchivoAlumIndice.read((char *)&IndiceAlumno, sizeof(indice));

        if (legajo == IndiceAlumno.Legajo)
        {
            return 1;
        }
        else
        {
            if (IndiceAlumno.Legajo < legajo)
            {
                fin = medio - 1;
            }
            else
            {
                fin = medio + 1;
            }
        }
    }
    ArchivoAlumIndice.close();
    return 0;
}

// Ordenamiento del indice mediate metodo Burbuja
void OrdenamientoIndice()
{
    // Abro tanto para escritura como lectura al indice
    fstream ArchivoIndice;
    ArchivoIndice.open("AIndice.inx", ios::binary | ios::in | ios::out);

    // Abro para lectura al archivo Maestro
    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Alumnos.dat", ios::binary);
    // Posiciono el puntero
    ArchivoMaestro.seekg(0, ios::end);

    // Declaro una estructura auxiliar del Indice
    struct indice IndiceAUX;

    // Defino las variables del ciclo
    int pos = ArchivoMaestro.tellg();
    ArchivoMaestro.close();
    int Elementos = pos / sizeof(Persona);

    for (int i = 0; i < Elementos; i++)
    {
        for (int j = 0; j < Elementos; j++)
        {
            ArchivoIndice.seekg(j * sizeof(IndiceAlumno), ios::beg);
            ArchivoIndice.read((char *)&IndiceAUX, sizeof(IndiceAlumno));
            ArchivoIndice.read((char *)&IndiceAlumno, sizeof(IndiceAlumno));

            if (IndiceAUX.Legajo < IndiceAlumno.Legajo)
            {
                ArchivoIndice.seekp(j * sizeof(IndiceAlumno));
                ArchivoIndice.write((char *)&IndiceAlumno, sizeof(IndiceAlumno));
                ArchivoIndice.write((char *)&IndiceAUX, sizeof(IndiceAlumno));
            }
        }
    }
    // Finalizado el cliclo cierro el el archivo de Indices
    ArchivoIndice.close();
}

void ListarAlumnos()
{
    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Alumnos.dat", ios::binary);

    /*
    ifstream ArchivoIndice;
    ArchivoIndice.open("Indice.inx", ios::binary);*/

    while (!ArchivoMaestro.read((char *)&DatosAlumno, sizeof(Persona)).eof())
    {
        //if (!ArchivoMaestro.eof())
        
            cout << "Alumno: " << ArchivoMaestro.tellg() / sizeof(Persona) << endl;
            cout << "Nombre: " << DatosAlumno.Nombre << endl;
            cout << "Apellido: " << DatosAlumno.Apellido << endl;
            cout << "Edad: " << DatosAlumno.Edad << endl;
            cout << "Nota: " << DatosAlumno.Nota << endl;
            cout << "Legajo: " << DatosAlumno.Legajo << endl;
            cout << "Materia:" << DatosAlumno.Materia << endl;
        
    }
    ArchivoMaestro.close();
    /*
        ifstream ArchivoAlumIndice;
        ArchivoAlumIndice.open("Indice.inx", ios::binary);
        int medio;
        int inicio = 0;
        ArchivoAlumIndice.seekg(0, ios::end);
        int fin = (ArchivoAlumIndice.tellg() / sizeof(indice) - 1);

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            ArchivoAlumIndice.seekg(medio * sizeof(indice));
            ArchivoAlumIndice.read((char *)&IndiceAlumno, sizeof(indice));

            if (DatosAlumno.Legajo == IndiceAlumno.Legajo)
            {
                DatosAlumno.Nombre;
                DatosAlumno.Apellido;
                DatosAlumno.Edad;
                DatosAlumno.Nota;
                DatosAlumno.Legajo;
                DatosAlumno.Materia;
            }
            else
            {
                if (IndiceAlumno.Legajo < DatosAlumno.Legajo)
                {
                    fin = medio - 1;
                }
                else
                {
                    fin = medio + 1;
                }
            }
        }
        ArchivoAlumIndice.close();*/
}

void BuscarAlumno()
{
    int LegajoAux = 0;

    cout << "Ingrese el legajo del alumno: ";
    cin >> LegajoAux;

    // Abro archivo de indice para lectura, binary | in
    ifstream ArchivoIndice;
    ArchivoIndice.open("AIndice.inx", ios::binary | ios::in);

    //Abro archivo maestro para la posicion
    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Alumnos.dat",ios::binary);
    //Lo posiciono
    ArchivoMaestro.seekg(0,ios::end);

    //Defino las variables del ciclo
    int posicion = ArchivoMaestro.tellg();
    int fin = (posicion/sizeof(DatosAlumno));
    int medio;
    int inicio = 0;
    int encontrado = 0;
    ArchivoMaestro.close();

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        //Me posiciono en el medio del archivo
        ArchivoIndice.seekg(medio * sizeof(IndiceAlumno));
        ArchivoIndice.read((char*)&IndiceAlumno,sizeof(IndiceAlumno));

        //Si mi LegajoAux coincide con un legajo guardado en el indice pasare a mostrar los datos
        if (IndiceAlumno.Legajo == LegajoAux)
        {
            ifstream ArchivoMaestro;
            ArchivoMaestro.open("Alumno.dat",ios::binary);
            ArchivoMaestro.seekg(IndiceAlumno.Posicion);
            ArchivoMaestro.read((char*)&DatosAlumno,sizeof(DatosAlumno));

            cout << "Legajo N° " <<DatosAlumno.Legajo<<"encontrado!"<<endl;
            cout << "Nombre: " <<DatosAlumno.Nombre<<endl;
            cout << "Apellido: " <<DatosAlumno.Apellido<<endl;
            cout << "Edad: " <<DatosAlumno.Edad<<endl;
            cout << "Materia: " <<DatosAlumno.Materia<<endl;
            cout << "Nota: " <<DatosAlumno.Nota<<endl;
            cout << endl;

            encontrado = 1;
            fin = - 1;
        }
        else
        {
            if (LegajoAux > IndiceAlumno.Legajo)
            {
                fin = medio - 1;
            }
            else
            {
                fin = medio + 1;
            }
            
        }
        if (encontrado != 1)
        {
            cout << "No se encontro el Legajo";
            cout << endl;
            exit (1);
        }
        
    }
    

}