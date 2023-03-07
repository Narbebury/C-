//Generar numeros del 1 a 10 y mostarlo en pantalla o guardarlo en un archivo

using namespace std;

#include <iostream>
#include <fstream>

void Mostrar(int);
void Guardar(int);

main()
{
    int num1;
    int num2;
    char salida; // P:pantalla o A:Archivo

    cout << "Selecciona la salida de los datos:";
    cin >> salida;
    

    //Generar numeros entre a y b
    for(int i = num1; i < num2+1; i++)
    {
    if (salida == 'A')

        Guardar(0);
    else //P

        Mostrar(0);
    }
}

void Mostrar(int num)
{
    cout << num << endl;
}

void Guardar(int num)
{
    //Archivos de salida (Escritura)

    // 1)crear el tipo de archivo con ofstream

    ofstream archivo;

    // 2)Abrir el archivo
    archivo.open("Numeros.txt", ios::app);// con el app se evita el borrado del archivo cada vez que se abre y se agregan los datos a los datos ya dispuestos
    
    // 3) Operacion
    archivo << num << endl;
    
    // 4) Forzar el buffer(Opcional)
    archivo.flush();
    
    // 5) Cerrar
    archivo.close();
}