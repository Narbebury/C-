/*B) Cargamos alumnos
Para verificar la carga de alumnos, se nos solicita desarrollar la funcionalidad de lectura del archivo de alumnos.txt.

Para ello, desarrollar una función Mostrar() que recorra el archivo de alumnos y muestre uno a uno los Apellidos y Nombres contenidos.

Mostrar al final la cantidad de alumnos cargados en el archivo.

Características del archivo
    • Archivo tipo texto, nombre: alumnos.txt
    • Grabado por flujos, un alumno por fila
    • Si el archivo contenía alumnos, se agregaron al final. */
using namespace std;

#include <iostream>
#include <fstream>

void guardar();

string Matriz[4][2];
main()
{
    char Nombre[20], Apellido[20];

    for (int i = 0; i < 4; i++)
    {
       cout << "Ingrese nombre";
       cin >> Nombre;
       cout << "Ingrese el apellido";
       cin >> Apellido;

       Matriz[i][0] = Nombre;
       Matriz[i][1] = Apellido;
       


    }
    guardar();



}

void guardar()
{
    ofstream archivo;
    archivo.open("Alunos.txt", ios::app);
    
    for (int i = 0; i < 4; i++)
    {
      archivo << Matriz[i][0] << ends;
      archivo << Matriz[i][1] << endl;    
    }
    
    archivo.flush();
    archivo.close();


}