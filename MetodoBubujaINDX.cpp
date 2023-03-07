#include <iostream>

using namespace std;

int main()
{

    // Ordeno el indice por metodo burbuja.
    fstream archIndx;
    archIndx.open("Entregas.inx", ios::binary | ios::in | ios::out);

    ifstream archEntrega;
    archEntrega.open("Entregas.dat", ios::binary);
    archEntrega.seekg(0, ios::end);

    struct indx IAuxiliar;

    int pos = archEntrega.tellg();
    archEntrega.close();

    int ielementos = pos / sizeof(empleado);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            archIndx.seekg(j * sizeof(Indice), ios::beg);
            archIndx.read((char *)&IAuxiliar, sizeof(Indice));
            archIndx.read((char *)&Indice, sizeof(Indice));

            if (strcmp(IAuxiliar.Legajo, Indice.Legajo) == 1)
            {
                archIndx.seekp(j * sizeof(Indice));
                archIndx.write((char *)&Indice, sizeof(Indice));
                archIndx.write((char *)&IAuxiliar, sizeof(Indice));
            }
        }
    }

    archIndx.close();
}