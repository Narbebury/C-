#include <iostream>
using namespace std;

int suma;
int num1 = 2;
int num2 = 4;

void funcion(){
    cout <<"Funcion sin valor de retorno"<< endl;
}

int sumar(int a, int b)
{
    return (a) + (b);
}

int main()
{
    suma = sumar(num1, num2);
    cout << "La suma es: "<< suma << endl;
    funcion();
    //cin.get();//No cierra la pantalla
    return 0;
}