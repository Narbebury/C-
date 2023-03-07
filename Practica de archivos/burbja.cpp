#include <iostream>

using namespace std;

int main()
{
    int Lista[10] = {1, 8, 3, 4, 5, 9, 6, 7, 2, 0};
    int aux = 0;
    int elementos = 10;

    cout << "Imprimo vector sin ordenar" << endl;

    for (int i = 0; i < elementos; i++)
    {
        cout << "Lista[" << i << "]: " << Lista[i] << endl;
    }
    cout << endl;

    for (int i = 1; i < elementos; i++)
    {
        for (int j = 0; j < elementos - i; j++)
        {
            if (Lista[j] > Lista[j + 1])
            {
                aux = Lista[j];
                Lista[j] = Lista[j + 1];
                Lista[j + 1] = aux;
            }
        }
    }

    cout <<"Vector ordenado de menor a mayor"<<endl;
    for (int i = 0; i < elementos; i++)
    {
        cout << "Lista[" << i << "]: " << Lista[i] << endl;
    }

    return 0;
}