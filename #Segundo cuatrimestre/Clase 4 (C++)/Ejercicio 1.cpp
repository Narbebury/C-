#include <iostream>
using namespace std;

int main()
{
    cout << "Hola mundo C++";

    cout << "Hola mundo C++" << endl;

    cout << "El total es: " << 5 << endl;
    cout << 100 << 200 << 300 << 400 << endl;

    cout.precision(3);
    cout << 3.5667 << endl;

    cout.width(10); //Lo que imprimo tiene como maximo 10 valores xxxx
    cout.fill('Z');//zzzzz
    cout.setf(ios::left); //(Especifica input output stream)De que lado quiero que complete los lugares que no informe
    cout << 20 << endl; //Muestra datos por pantalla

    cout.width(10);
    cout.fill('Z');
    cout << left << 20 << endl;

    cout << endl << endl;

    cout.width(10);
    cout.fill('X');
    cout.setf(ios::right);
    cout << 30 << endl;

    cout.width(10);
    cout.fill('X');
    cout << right << 30 << endl;
    
    cout << endl << endl;

    printf("Hola mundo C++");
    printf("Hola mundo C++ \n");
    printf("El total es: %i \n", 5);
    printf("%i%i%i%i \n", 100,200,300,400);
    printf("%2.f \n",3.5667);
}