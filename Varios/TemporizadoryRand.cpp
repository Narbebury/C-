/*Cuanto tarda una persona en adivinar un numero
Se pide ingresar un numero minimo y un numero maximo y va a generar
un numero aleatorio entre ese intervalo*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0)); // Semilla
    int min, max, aleatorio, intentos = 0, n;

    cout << "Ingrese minimo: ";
    cin >> min;
    cout << endl;
    cout << "Ingrese maximo: ";
    cin >> max;

    cout << RAND_MAX << endl;                   // muestro el valor de la constante rand max
    aleatorio = min + rand() % (max - min + 1); // Empieza en minimo

    clock_t t;
    t = clock();

    do
    {
        cout << "Adivine: ";
        cin >> n;
        intentos++;
    } while (n != aleatorio);

    t = clock() - t;
    cout << "Acertaste! El numero generado fue: " << aleatorio;
    cout << endl;
    cout << "Realizaste " << intentos << " intentos" << endl;
    cout <<"Durante "<<float(t)/CLOCKS_PER_SEC<<"segundos";
    return 0;
}