#include <iostream>
#include <cmath> //Para poder usar sqrt(Nos permite usar raices cuadradas)
using namespace std;

int main(){
    double cateto1, cateto2, hipotenusa;
    
    cout <<"Introduzca las longitudes de los catetos: ";
    cin >> cateto1>>cateto2;
    hipotenusa= sqrt(cateto1*cateto1+cateto2*cateto2);
    cout <<"La longitud de la hipotenusa es: "<< hipotenusa << endl;
}