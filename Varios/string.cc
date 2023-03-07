#include <iostream>
#include <string>

using namespace std;

int main()
{
    string cadena1 = "Hola";

    cout << "Ingrese texto: ";
    cin >> cadena1;

    fflush(stdin);
    cout << endl;
    // cambiar el valor del string cadena1
    cout << "Introduce el nuevo valor: ";
    getline(cin, cadena1);

    cout << "Has introducido lo siguiente: " << cadena1 << endl;

    // lenght() Saber la cantidad de caracteres de una variable

    cout << "Longitud del string introducido: " << cadena1.length() << endl;

    // substr() Nos permite extraer un substring del string seleccionado
    string cadena2 = "mafia";

    cout << "Extrayendo ma: " << cadena2.substr(0, 2) << endl; // para ma
    cout << "Extrayendo ia: " << cadena2.substr(3, 2) << endl;
    cout << "Extrayendo fi: " << cadena2.substr(2, 2) << endl;

    // find Busca la primera ocurrencia de un string en el string seleccionado
    string cadena3 = "Busca algo dentro de mi";
    string Buscar = "";

    cout << "Introduce una busqueda para \"" << cadena3 << "\":";
    getline(cin, Buscar);

    // size_t es un tipo capaz de representar el tamaño de cualquier objeto en bytes
    // Es utilizado como aguja cuando se realizan búsquedas en strings y nos regresará un numero
    // con la primera ocurrencia de un string, de lo contrario sera igual a string::npos
    // npos: es un valor constante con el mayor valor posible para un elemento del tipo size_t
    size_t aguja = cadena3.find(Buscar); // Busca algo dentro del string

    if (aguja != string::npos)
    {
        cout << Buscar << "ha sido encontrado en la posicion: " << aguja;
    }
    else
    {
        cout << Buscar << " No ha sido encontrado" << endl;
    }
}