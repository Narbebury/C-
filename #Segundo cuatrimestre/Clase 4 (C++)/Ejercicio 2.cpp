#include <iostream>
#include <string> //ACEPTA DATOS DE CADENA STRING

using namespace std;

int main()
{
    int iVariable;
    cout << "Ingresa un numero: ";
    cin >> iVariable;
    cout << "Numero: " << iVariable << endl;

    char cVariable;
    cout << "Ingresa una letra:" << endl;
    cin >> cVariable;
    cout << " Caracter:: " << cVariable << endl;

    string sVariable; //Cadenas --> arreglo[]
    cout << "Ingresa una cadena " << endl;
    cin >> sVariable; //No puede tener espacios
    cout << "Mi cadena sin espacio es: " << sVariable << endl;

    string sVariableEspacios;
    cin.ignore();
    cout << "Ingresa una cadena con espacio " << endl;
    getline(cin, sVariableEspacios); //getline es para saltar la linea cuando aprete ENTER. Si puede tener espacios
    cout << sVariableEspacios << endl;
}