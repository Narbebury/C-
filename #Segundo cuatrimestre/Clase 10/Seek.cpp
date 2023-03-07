using namespace std;

#include <iostream>
#include <fstream>

main()
{
    struct str
    {
        int codigo;
    };

    struct str estructura;

    fstream archivo;
    archivo.open("seek.txt", ios::binary | ios::out);

    cout << "Cursor en posicion INICIAL: " << archivo.tellp() << endl;

    estructura.codigo = 100;
    archivo.write((char *)&estructura, sizeof(estructura));

    cout << "Cursor en la posicion 2 REGISTRO: " << archivo.tellp() << endl;
    archivo.seekp(posicion); //archivo.seekp(posicion, ios::beg)

    cout << "Cursor DESPUES de la posicion SEEK: " << archivo.tellp() << endl;

    estructura.codigo = 100;
    archivo.write((char *)&estructura, sizeof(estructura));

    cout << "Cursor DESPUES de posicion SEEK + WRITE: " << archivo.tellp() << endl;

    cout << "FIN" << endl;
    archivo.close();
}