/*Programa de venta de electrodomesticos
el programa dara de alta un cliente, el cual sera validado con su cuil,
*/
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct cliente
{
    char Nombre[100];
    char Apellido[100];
    long long Cuil;
};

struct indiceP
{
    long long CuilPar;
    int posicion;
};

struct indiceI
{
    long long CuilImpar;
    int posicion;
};

struct cliente DatosCliente;
struct indiceP IndicePar;
struct indiceI IndiceImpar;

void AltaCliente();
int ValidoCliente(long long CuilAux);
void BuscarCliente();
//void ListarCliente();
void OrdenarIndicePar();
void OrdenarIndiceImpar();

int main()
{
    int opcion = 0;
    int opcion2 = 0;

    do
    {
        cout << "BIENVENIDO!" << endl;
        cout << "Menu" << endl;
        cout << "1 - Venta" << endl;
        cout << "2 - Buscar Cliente" << endl;
        cout << "3 - Listar Clientes" << endl;
        cout << "4 - Salir" << endl;
        cin >> opcion;
        cout << endl;
        fflush(stdin);

        switch (opcion)
        {
        case 1:
            AltaCliente();
            break;

        case 2:
            BuscarCliente();
            break;

        case 3:
            //ListarCliente();
            break;

        case 4:
            cout << "Esta seguro que quiere salir ?" << endl;
            cout << "1 - Si \n2 - No" << endl;
            cin >> opcion2;
            if (opcion2 == 1)
            {
                cout << "Hasta luego...";
                exit(1);
            }
            else
            {
                cout << endl;
                return main();
            }

        default:
            cout << "Opcion incorrecta!" << endl;
            return main();
            break;
        }
    } while (opcion != 4);
}

void AltaCliente()
{
    cout << "Ingrese el cuil del cliente: ";
    cin >> DatosCliente.Cuil;
    fflush(stdin);

    int valida = -1;

    // Defino el archivo Maestro
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("Ventas.dat", ios::binary | ios::app | ios::ate);

    if (ArchivoMaestro.fail())
    {
        cout << "Error al abrir el archivo";
        exit(1);
    }

    valida = ValidoCliente(DatosCliente.Cuil);

    if (DatosCliente.Cuil == 1)
    {
        int op = 0;
        cout << "El Documento ingresado ya existe" << endl;
        cout << "Quiere ingresar a otra persona ?" << endl;
        cout << "1 - Si" << endl;
        cout << "2 - No" << endl;
        cin >> op;
        fflush(stdin);
        cout << endl;

        if (op == 1)
        {
            return AltaCliente();
        }
        else
        {
            cout << "Hasta luego!";
        }
    }
    else
    {
        cout << "Ingrese el Nombre: ";
        cin.getline(DatosCliente.Nombre, 100);
        fflush(stdin);
        cout << "Ingrese el Apellido: ";
        cin.getline(DatosCliente.Apellido, 100);
        fflush(stdin);

        // Guardo datos en archivo maestro;
        ArchivoMaestro.write((char *)&DatosCliente, sizeof(DatosCliente));

        // Guardo datos del cliente dependiendo si el cuil es par o impar en su respectivo indice
        if (DatosCliente.Cuil % 2 == 0)
        {
            ofstream ArchivoIndicePar;
            ArchivoIndicePar.open("EIndiceP.inx", ios::binary | ios::app | ios::ate);

            IndicePar.posicion = ArchivoMaestro.tellp();
            IndicePar.posicion = IndicePar.posicion - sizeof(DatosCliente);
            IndicePar.CuilPar = DatosCliente.Cuil;
            // Escribo en indice par
            ArchivoIndicePar.write((char *)&IndicePar, sizeof(IndicePar));
            ArchivoIndicePar.close();
        }
        else
        {
            ofstream ArchivoIndiceImpar;
            ArchivoIndiceImpar.open("EIndiceI.inx", ios::binary | ios::app | ios::ate);
            IndiceImpar.posicion = ArchivoMaestro.tellp();
            IndiceImpar.posicion = IndiceImpar.posicion - sizeof(DatosCliente);
            IndiceImpar.CuilImpar = DatosCliente.Cuil;
            ArchivoIndiceImpar.write((char *)&IndiceImpar, sizeof(IndiceImpar));
            ArchivoIndiceImpar.close();
        }
        ArchivoMaestro.close();
        cout << endl;
        // Llamo a la funcion ordenar indice par e impar
        OrdenarIndicePar();
        OrdenarIndiceImpar();
    }
}

// La funcion Validara el cuil del cliente mediante la busqueda binaria
int ValidoCliente(long long CuilAux)
{
    if (CuilAux % 2 == 0)
    {
        ifstream ArchivoIP;
        ArchivoIP.open("EIndiceP.inx", ios::binary);
        int medio;
        int inicio;
        ArchivoIP.seekg(0, ios::end);
        int fin = (ArchivoIP.tellg() / sizeof(indiceP) - 1);

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            ArchivoIP.seekg(medio * sizeof(indiceP));
            ArchivoIP.read((char *)&IndicePar, sizeof(indiceP));

            if (CuilAux == IndicePar.CuilPar)
            {
                return 1;
            }
            else
            {
                if (IndicePar.CuilPar < CuilAux)
                {
                    fin = medio - 1;
                }
                else
                {
                    inicio = medio + 1;
                }
            }
        }
        ArchivoIP.close();
        return 0;
    }
    else
    {
        ifstream ArchivoI;
        ArchivoI.open("EIndiceI.inx", ios::binary);
        int medio;
        int inicio;
        ArchivoI.seekg(0, ios::end);
        int fin = (ArchivoI.tellg() / sizeof(indiceI) - 1);

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            ArchivoI.seekg(medio * sizeof(indiceI));
            ArchivoI.read((char *)&IndicePar, sizeof(indiceI));

            if (CuilAux == IndiceImpar.CuilImpar)
            {
                return 1;
            }
            else
            {
                if (IndiceImpar.CuilImpar < CuilAux)
                {
                    fin = medio - 1;
                }
                else
                {
                    inicio = medio + 1;
                }
            }
        }
        ArchivoI.close();
    }
}

void OrdenarIndicePar()
{
    // Ordeno el indice por metodo burbuja.
    fstream ArchivoIndex;
    ArchivoIndex.open("EIndiceP.inx", ios::binary | ios::in | ios::out);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Ventas.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);

    struct indiceP IAuxiliar;

    int pos = ArchivoMaestro.tellg();
    ArchivoMaestro.close();

    int ielementos = pos / sizeof(cliente);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            ArchivoIndex.seekg(j * sizeof(IndicePar), ios::beg);
            ArchivoIndex.read((char *)&IAuxiliar, sizeof(IndicePar));
            ArchivoIndex.read((char *)&IndicePar, sizeof(IndicePar));

            if (IAuxiliar.CuilPar < IndicePar.CuilPar)
            {
                ArchivoIndex.seekp(j * sizeof(IndicePar));
                ArchivoIndex.write((char *)&IndicePar, sizeof(IndicePar));
                ArchivoIndex.write((char *)&IAuxiliar, sizeof(IndicePar));
            }
        }
    }

    ArchivoIndex.close();
}

void OrdenarIndiceImpar()
{
    // Ordeno el indice por metodo burbuja.
    fstream ArchivoIndex;
    ArchivoIndex.open("EIndiceI.inx", ios::binary | ios::in | ios::out);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("Ventas.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);

    struct indiceI IAuxiliar;

    int pos = ArchivoMaestro.tellg();
    ArchivoMaestro.close();

    int ielementos = pos / sizeof(cliente);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            ArchivoIndex.seekg(j * sizeof(IndiceImpar), ios::beg);
            ArchivoIndex.read((char *)&IAuxiliar, sizeof(IndiceImpar));
            ArchivoIndex.read((char *)&IndiceImpar, sizeof(IndiceImpar));

            if (IAuxiliar.CuilImpar < IndiceImpar.CuilImpar)
            {
                ArchivoIndex.seekp(j * sizeof(IndiceImpar));
                ArchivoIndex.write((char *)&IndiceImpar, sizeof(IndiceImpar));
                ArchivoIndex.write((char *)&IAuxiliar, sizeof(IndiceImpar));
            }
        }
    }

    ArchivoIndex.close();
}

void BuscarCliente()
{
    long long CuilAux;

    cout << "Ingrese el Documento del Cliente a buscar: ";
    cin >> CuilAux;
    cout << endl;
    if (CuilAux % 2 == 0)
    {
        // Busco en indice por Busqueda Binaria.
        ifstream IndxEntregas;
        IndxEntregas.open("EIndiceP.inx", ios::binary | ios::in);

        ifstream archivoDatos;
        archivoDatos.open("Ventas.dat", ios::binary);
        archivoDatos.seekg(0, ios::end);
        int posicion = archivoDatos.tellg();
        int fin = (posicion / sizeof(DatosCliente)) - 1;
        archivoDatos.close();

        int medio;
        int inicio = 0;
        int encontrado = 0;

        while (inicio <= fin)
        {

            medio = (fin + inicio) / 2;

            // Posiciono en el medio del archivo
            IndxEntregas.seekg(medio * sizeof(IndicePar));
            IndxEntregas.read((char *)&IndicePar, sizeof(IndicePar));

            if (IndicePar.CuilPar == CuilAux)
            {
                // Muestro los datos de las entregas.
                ifstream archivoEntregas;
                archivoEntregas.open("Ventas.dat", ios::binary);
                archivoEntregas.seekg(IndicePar.posicion);
                archivoEntregas.read((char *)&DatosCliente, sizeof(DatosCliente));

                cout << "" << DatosCliente.Nombre << "||" << DatosCliente.Apellido << endl;
                cout << "Cuil: "<<DatosCliente.Cuil;
                // cout << "Documento: " << Datos_Cliente.Documento << endl;
                // cout << "Domicilio: " << Datos_Cliente.Domicilio << endl;
                // cout << "Producto: " << Datos_Cliente.Producto << endl;
                // cout << "Precio: " << Datos_Cliente.Precio << endl;
                // cout << "Cantidad: " << Datos_Cliente.cantidad << endl;

                encontrado = 1;
                fin = -1;
                archivoEntregas.close();
                archivoDatos.close();
            }
            else
            {
                if (CuilAux > IndicePar.CuilPar)
                    fin = medio - 1;
                else
                    inicio = medio + 1;
            }
        }
        if (encontrado != 1)
        {
            cout << "No se encontro el Cuil buscado" << endl;
        }
    }
    else
    {
        ifstream Iimpar;
        Iimpar.open("EIndiceI.inx", ios::binary | ios::in);

        ifstream archivoDatos;
        archivoDatos.open("Ventas.dat", ios::binary);
        archivoDatos.seekg(0, ios::end);
        int posicion = archivoDatos.tellg();
        int fin = (posicion / sizeof(DatosCliente)) - 1;
        archivoDatos.close();

        int medio;
        int inicio = 0;
        int encontrado = 0;

        while (inicio <= fin)
        {

            medio = (fin + inicio) / 2;

            // Posiciono en el medio del archivo
            Iimpar.seekg(medio * sizeof(IndiceImpar));
            Iimpar.read((char *)&IndiceImpar, sizeof(IndiceImpar));

            if (IndiceImpar.CuilImpar == CuilAux)
            {
                // Muestro los datos de las entregas.
                ifstream archivoEntregas;
                archivoEntregas.open("Ventas.dat", ios::binary);
                archivoEntregas.seekg(IndiceImpar.posicion);
                archivoEntregas.read((char *)&DatosCliente, sizeof(DatosCliente));

                cout << "" << DatosCliente.Nombre << "||" << DatosCliente.Apellido << endl;
                cout << "Cuil: "<<DatosCliente.Cuil;
                // cout << "Documento: " << Datos_Cliente.Documento << endl;
                // cout << "Domicilio: " << Datos_Cliente.Domicilio << endl;
                // cout << "Producto: " << Datos_Cliente.Producto << endl;
                // cout << "Precio: " << Datos_Cliente.Precio << endl;
                // cout << "Cantidad: " << Datos_Cliente.cantidad << endl;

                encontrado = 1;
                fin = -1;
                 archivoEntregas.close();
                archivoDatos.close();
            }
            else
            {
                if (CuilAux > IndiceImpar.CuilImpar)
                    fin = medio - 1;
                else
                    inicio = medio + 1;
            }
        }
        if (encontrado != 1)
        {
            cout << "No se encontro el Cuil buscado" << endl;
        }
    }
    
}



//void ListarCliente();
