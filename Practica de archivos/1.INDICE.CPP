#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

void Cargar_Alumno();
void Buscar_Alumno();
void Listar_Alumno();

struct alumno
{
    char Nombre[30];
    char Apellido[30];
    char Materia[30];
    int Documento;
};

struct index
{
    int Documento;
    int posicion;
};

struct index IndiceAlumnos;
struct alumno DatosAlumnos;

int main()
{
    int op = 0;
    int op2 = 0;

    do
    {
        cout << endl;
        cout << "MENU" << endl;
        cout << "1 - Cargar Alumno" << endl;
        cout << "2 - Buscar Alumno" << endl;
        cout << "3 - Listar Alumnos" << endl;
        cout << "4 - Salir" << endl;
        cin >> op;

        switch (op)
        {
        case 1:
            Cargar_Alumno();
            break;

        case 2:
            Buscar_Alumno();
            break;

        case 3:
            Listar_Alumno();
            break;

        case 4:
            cout << "Esta seguro que quiere salir ?";
            cout<<endl;
            cout<<"1 - No";
            cout<<endl;
            cout<<"2 - Si";
            cout<<endl;
            cin >> op2;

            if (op2 == 1)
            {
                return main();
            }
            if (op2 == 2)
            {
                cout << "Hasta luego...";
                exit(1);
            }

            break;

        default:
            break;
        }
    } while (op2 != 4);
}

void Cargar_Alumno()
{
    fstream CargAlum;
    CargAlum.open("Alumnos.dat", ios::binary | ios::app | ios::ate | ios::out);

    fstream archAlumIndice;
    archAlumIndice.open("Alumnos.indx", ios::binary | ios::app | ios::ate | ios::out);

    if (CargAlum.fail())
    {
        cout << "Error al abrir el archivo";
        exit(1);
    }
    
    cout << "Ingrese el Nombre: ";
    cin.ignore();
    cin.getline(DatosAlumnos.Nombre, 30);
    cout << endl;
    fflush(stdin);
    cout << "Ingrese el Apellido: ";
    cin.ignore();
    cin.getline(DatosAlumnos.Apellido, 30);
    cout << endl;
    cout << "Ingrese la Materia: ";
    cin >> DatosAlumnos.Materia;
    cout << endl;
    cout << "Ingrese el Documento: ";
    cin >> DatosAlumnos.Documento;

    IndiceAlumnos.Documento = DatosAlumnos.Documento;
    IndiceAlumnos.posicion = CargAlum.tellg();
    CargAlum.write((char *)&DatosAlumnos, sizeof(DatosAlumnos));
    archAlumIndice.write((char *)&IndiceAlumnos, sizeof(IndiceAlumnos));
    archAlumIndice.close();
    CargAlum.close();
}

void Buscar_Alumno()
{
    int DocumentoAux;
    fstream busqAlum;
    busqAlum.open("Alumnos.indx", ios::binary | ios::in);

    cout << "Ingrese el Documento del Alumno a buscar";
    cin >> DocumentoAux;
}

void Listar_Alumno()
{
    fstream ListarAlum;
    ListarAlum.open("Alumnos.dat", ios::binary | ios::in);

    while (ListarAlum.read((char *)&DatosAlumnos, sizeof(DatosAlumnos)))
    {
        cout << "Nombre: " << DatosAlumnos.Nombre;
        cout << endl;
        cout << "Apellido: " << DatosAlumnos.Apellido;
        cout << endl;
        cout << "Materia: " << DatosAlumnos.Materia;
        cout << endl;
        cout << "Documento: " << DatosAlumnos.Documento;
        cout << endl;
    }
}