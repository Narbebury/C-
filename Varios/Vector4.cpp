/* Programa que defina 2 vectores de caracteres y después almacene
el contenido de ambos vectores en un nuevo vector, situado en promer lugar
los elementos del primer vector seguido de los elementos del 
segundo vector. Muestre el contenido del nuevo vector
en la salida estándar */
#include <iostream>

using namespace std;

int main()
{
    char Vector1[] = {'a','b','c','d'};
    char Vector2[] = {'e','f','g','h','i'};
    char Vector3[10];


    //Copio los elementos Vector1 a Vector3
    for (int i = 0; i < 5; i++)
    {
        Vector3[i] = Vector1[i];
    }
    
    //Copio los elmentos de Vector2 a Vector3
    for (int i = 5; i < 10; i++)
    {
        Vector3[i] = Vector2[i-5];
    }
    
    //Muestro el vector

    for (int i = 0; i < 10; i++)
    {
        cout<<Vector3[i]<<endl;
    }
    

    return 0;
}