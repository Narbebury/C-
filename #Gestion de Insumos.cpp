/*Programa de Gestion de insumos informaticos.
Mediante la funcion entrega se realiza la carga de los insumos informaticos, solicitando el legajo el empleado y mediante la funcion Validar compruebo que el mismo este o no cargado
en el archivo de indice. Si la persona no esta cargada continuo con la carga de datos en el archivo principal, caso contrario muestro el legajo del empleado por pantalla.
Uso la función Indexar para ordenar los indices mediante el método burbuja y la funcion Listar para ver por pantalla los legajos sin indexar o indexados dependiendo si el usuario
hizo la indexación 

Agustin Narbebury   */

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct empleado
{
    char Legajo[10];
    int Codigo_insumo;
    char Nombre_insumo[50];
    int Cantidad_entregada;
};

struct indx
{
    int posicion;
    char Legajo[10];
};

struct indx Indice;
struct empleado Empleado;

// Defino los prototipos de las funciones.
void Entrega();
int Validar(char LegajoAux[10]);
void Mostrar();
void Buscar();
void Listar();
void Indexar();

int main()
{
    char op;
    int op2;

    do
    {
        cout << "MENU" << endl;
        cout << "E - Entrega de insumos" << endl;
        cout << "B - Buscar entrega por legajo" << endl;
        cout << "R - Reporte de entregas ordenado por Legajo: " << endl;
        cout << "I - Indexar" << endl;
        cout << "L - Listar" << endl;
        cout << "S - Salir" << endl;
        cin >> op;

        if (op == 'E' || op == 'e')
        {
            Entrega();
        }
        if (op == 'B' || op == 'b')
        {
            Buscar();
        }
        if (op == 'R' || op == 'r')
        {
            Mostrar();
        }
        if (op == 'I' || op == 'i')
        {
            Indexar();
        }

        if (op == 'L' || op == 'l')
        {
            Listar();
        }

        if (op == 'S' || op == 's')
        {
            cout << "Esta seguro que quiere salir?" << endl;
            cout << "1 - Si" << endl;
            cout << "2 - No" << endl;
            cin >> op2;

            if (op2 == 1)
            {
                cout << "Hasta luego...";
                return 1;
            }
            else
            {
                return main();
            }
        }

    } while (op != 'S');

    return 0;
}

void Entrega()
{

    int valido = -1;
    ofstream archEntrega;
    archEntrega.open("Entregas.dat", ios::binary | ios::app | ios::ate);

    cout << "Ingrese el legajo del empleado: ";
    cin >> Empleado.Legajo;
    cout << endl;
    fflush(stdin);

    valido = Validar(Empleado.Legajo);

    // Valido la existencia del legajo
    if (valido == 1)
    {
        cout << "El Legajo ingresado ya existe";
        cout<<endl;
        Mostrar();
        cout << endl;
    }
    else
    {
        // Si el legajo no estaba cargado paso a cargar los datos en archivo principal.
        cout << "Ingrese el codigo del insumo: ";
        cin >> Empleado.Codigo_insumo;
        fflush(stdin);
        cout << endl;

        cout << "Ingrese el nombre del insumo: ";
        cin.getline(Empleado.Nombre_insumo, 50);
        cout << endl;

        cout << "Ingrese la cantidad entregada: ";
        cin >> Empleado.Cantidad_entregada;
        cout << endl;
        
        //Guardo datos en archivo principal.
        archEntrega.write((char *)&Empleado, sizeof(empleado));

        // Guardo datos en el indice.
        ofstream archIndice;
        archIndice.open("Entregas.inx", ios::binary | ios::app | ios::ate);
        Indice.posicion = archEntrega.tellp();
        Indice.posicion = Indice.posicion - sizeof(Empleado);
        strcpy(Indice.Legajo, Empleado.Legajo);
        archIndice.write((char *)&Indice, sizeof(Indice));

        archEntrega.close();
        archIndice.close();
    }
}

int Validar(char LegajoAux[10])
{
    // Valido por Busqueda Binaria.
    ifstream archivo;
    archivo.open("Entregas.inx", ios::binary);
    int medio;
    int inicio = 0;
    archivo.seekg(0, ios::end);
    int fin = (archivo.tellg() / sizeof(indx) - 1);

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        archivo.seekg(medio * sizeof(indx));
        archivo.read((char *)&Indice, sizeof(indx));

        if (strcmp(LegajoAux,Indice.Legajo ) == 0)
        {
            return 1;
        }
        else
        {
            if (strcmp(LegajoAux,Indice.Legajo) == -1)
            {
                fin = medio - 1;
            }
            else
            {
                inicio = medio + 1;
            }
        }
    }

    archivo.close();

    return 0;
}

void Indexar()
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

void Buscar()
{
    char LegajoAux[10];

    cout << "Ingrese el legajo a buscar: ";
    cin >> LegajoAux;
    cout << endl;

    // Busco en indice por Busqueda Binaria.
    ifstream IndxEntregas;
    IndxEntregas.open("Entregas.inx", ios::binary | ios::in);

    ifstream archivoDatos;
    archivoDatos.open("Entregas.dat", ios::binary);
    archivoDatos.seekg(0, ios::end);
    int posicion = archivoDatos.tellg();
    int fin = (posicion / sizeof(Empleado)) - 1;
    archivoDatos.close();

    int n;
    int medio;
    int inicio = 0;
    int encontrado = 0;

    while (inicio <= fin)
    {

        medio = (fin + inicio) / 2;

        // Posiciono en el medio del archivo
        IndxEntregas.seekg(medio * sizeof(Indice));
        IndxEntregas.read((char *)&Indice, sizeof(Indice));

        if (strcmp(Indice.Legajo, LegajoAux) == 0)
        {
            // Muestro los datos de las entregas.
            ifstream archivoEntregas;
            archivoEntregas.open("Entregas.dat", ios::binary);
            archivoEntregas.seekg(Indice.posicion);
            archivoEntregas.read((char *)&Empleado, sizeof(Empleado));

            cout << "Legajo del empleado: " << Empleado.Legajo;
            cout << endl;

            cout << "Cantidad entregada: " << Empleado.Cantidad_entregada;
            cout << endl;

            cout << "Codigo del insumo: " << Empleado.Codigo_insumo;
            cout << endl;

            cout << "Nombre del insumo: " << Empleado.Nombre_insumo;
            cout << endl;
            cout <<endl;

            encontrado = 1;
            fin = -1;
        }
        else
        {
            if (strcmp(LegajoAux, Indice.Legajo) == -1)
                fin = medio - 1;
            else
                inicio = medio + 1;
        }
    }
    if (encontrado != 1)
    {
        cout << "No se encontro el legajo buscado" << endl;
    }
}

void Mostrar()
{
    ifstream archivo;
    archivo.open("Entregas.inx", ios::binary);


    ifstream archivoEntregas;
    archivoEntregas.open("Entregas.dat",ios::binary);

    int i = 1;

    while (archivo.read((char *)&Indice, sizeof(Indice)))
    {
        if (!archivo.eof())
        {

            cout << "Legajo " << i << ": " << Indice.Legajo;
            cout<<endl;
            i++;
        }
    }

    archivo.close();
    archivoEntregas.close();
}

void Listar()
{
    Mostrar();
}