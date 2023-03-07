#include <iostream>
#include <string>

using namespace std;

struct persona
{
    string nombre;
    string apellido;
    string direccion;
} Persona;

int main()
{

    cout << "Ingrese el nombre: ";
    getline(cin, Persona.nombre);
    cout << endl;

    cout << "Ingrese el apellido: ";
    getline(cin, Persona.apellido);
    cout << endl;

    cout << "Ingrese la direccion: ";
    getline(cin, Persona.direccion);
    
    system("cls");

    cout << "Nombre: " << Persona.nombre;
    cout << endl;

    cout << "Apellido: " << Persona.apellido;
    cout << endl;

    cout << "Direccion: " << Persona.direccion;
    cout << endl;
}