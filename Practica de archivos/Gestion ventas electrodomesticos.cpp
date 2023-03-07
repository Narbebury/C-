/*Programa Venta de electrodomesticos
se dara de alta un cliente indicando su cuil, si pago o no, validacion */

#include <iostream>
#include <fstream>

using namespace std;

struct Persona
{
    char Nombre[50];
    char Apellido[50];
    int Edad;
    long long Documento;
    char Domicilio[50];
    char Localidad[50];
    char Producto[50];
    float Precio;
};

struct IndexPar
{
    int posicion;
    long long DocumentoIndxP;
};

struct IndexImpar
{
    int posicion;
    long long DocumentoIndxI;
};

struct Persona Cliente;
struct IndexPar IndxPar;
struct IndexImpar IndxImpar;

//DEFINO PROTOTIPO DE LAS FUNCIONES A UTILIZAR
void Alta();
int Valida_Alta(long long);
void BuscarCliente();
void Ordenar_IndicePar();
void Ordenar_IndiceImpar();
void listarIndicePar();
void listarIndiceImpar();
//void ReporteProdImpago();

int main()
{
    int op = 0;
    int op2 = 0;
    int op3 = 0;

    do
    {
        cout << "MENU" << endl;
        cout << "1 - Alta cliente" << endl;
        cout << "2 - Buscar Cliente" << endl;
        cout << "3 - Listar Clientes" << endl;
        cout << "4 - Reporte de productos impagos" << endl;
        cout << "5 - Salir" << endl;
        cin >> op;
        cout << endl;

        switch (op)
        {
        case 1:
            Alta();
            break;

        case 2:
            BuscarCliente();
            break;

        case 3:
            cout << "1 Para listar indices con documentos Par" << endl;
            cout << "2 - Para listar indices con documentos Impares" << endl;
            cin >> op3;

            if (op3 == 1)
            {
                listarIndicePar();
            }
            else
            {
                listarIndiceImpar();
            }

            system("cls");
            break;

        case 4:
            /* code */
            break;

        case 5:
            cout << "Esta seguro que quiere salir?" << endl;
            cout << "1 - Si" << endl;
            cout << "2 - No" << endl;
            cin >> op2;

            if (op2 == 1)
            {
                cout << "Hasta Luego!";
            }
            if (op2 == 2)
            {
                return main();
            }

            break;

        default:

            cout << "Ingrese una opcion correcta" << endl;
            cout << endl;
            return main();

            break;
        }

    } while (op != 5);
}

void Alta()
{
    ofstream archcliente;
    archcliente.open("Clientes.dat", ios::binary | ios::app | ios::ate);

    int valido = -1;

    cout << "Ingrese el Documento del cliente: ";
    cin >> Cliente.Documento;
    cout << endl;
    fflush(stdin);

    valido = Valida_Alta(Cliente.Documento);

    if (valido == 1)
    {
        cout << "El documento ingresado ya existe";
        cout << "Quiere dar de alta otra persona ?";
        cout << "1 - Si";
        cout << "2 - No";
        int op = 0;

        if (op == 1)
        {
            return Alta();
        }
        else
        {
            cout << "Hasta luego!";
        }

        cout << endl;
    }
    else
    {
        cout << "Ingrese el Nombre: ";
        cin.getline(Cliente.Nombre, 50);
        cout << endl;

        cout << "Ingrese Apellido: ";
        cin.getline(Cliente.Apellido, 50);

        cout << endl;
        cout << "Edad: ";
        cin >> Cliente.Edad;
        fflush(stdin);

        cout << "Ingrese el Domicilio: ";
        cin.getline(Cliente.Domicilio, 50);
        cout << endl;
        fflush(stdin);

        cout << "Ingrese la Localidad: ";
        cin.getline(Cliente.Localidad, 50);
        cout << endl;
        fflush(stdin);

        cout << "Ingrese el producto: ";
        cin.getline(Cliente.Producto, 50);
        fflush(stdin);

        cout << "Ingrese el precio: ";
        cin >> Cliente.Precio;
        fflush(stdin);

        //GUARDO DATOS EN ARCHIVO MAESTRO
        archcliente.write((char *)&Cliente, sizeof(Cliente)); //--> TELLP para el indice
        

        //GUARDO DATOS EN INDICE 1(PAR) si el Documento del cliente es par, caso contrario guardo en indice 2.
        if (Cliente.Documento % 2 == 0)
        {
            ofstream indiceClientes;
            indiceClientes.open("ClientesIPar.inx", ios::binary | ios::app | ios::ate);

            IndxPar.posicion = archcliente.tellp();
            IndxPar.posicion = IndxPar.posicion - sizeof(Cliente);
            IndxPar.DocumentoIndxP = Cliente.Documento;
            indiceClientes.write((char *)&IndxPar, sizeof(IndxPar));

            indiceClientes.close();
        }
        else
        {
            //GUARDO DATOS EN INDICE 2
            ofstream indiceClientes2;
            indiceClientes2.open("ClientesIImpar.inx", ios::binary | ios::app | ios::ate);

            IndxImpar.posicion = archcliente.tellp();
            IndxImpar.posicion = IndxImpar.posicion - sizeof(Cliente);
            IndxImpar.DocumentoIndxI = Cliente.Documento;
            indiceClientes2.write((char *)&IndxImpar, sizeof(IndxImpar));

            indiceClientes2.close();
        }

        //cout << "----------------------------------" << endl;
        //cout << "IMPRIMO INDICE 2" << endl;
        //ifstream INdice2;
        //INdice2.open("ClientesI2.inx", ios::binary);
        //int i = 1;
        //while (INdice2.read((char *)&Indice_2, sizeof(Indice_2)))
        //{
        //    cout << "rz: " << i << " " << Indice_2.Razon_Social;
        //    cout << endl;
        //    i++;
        //}
        //INdice2.close();
        archcliente.close();
        Ordenar_IndicePar();

        Ordenar_IndiceImpar();
    }
}

int Valida_Alta(long long DocumentoAux) // ES SECUENCIAL y PIDE BINARIOstruct cliente
{

    if (DocumentoAux % 2 == 0)
    {
        ifstream archivoPar;
        archivoPar.open("ClientesIPar.inx", ios::binary);
        int medio;
        int inicio = 0;
        archivoPar.seekg(0, ios::end);
        int fin = (archivoPar.tellg() / sizeof(IndexPar) - 1);

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            archivoPar.seekg(medio * sizeof(IndxPar));
            archivoPar.read((char *)&IndxPar, sizeof(IndxPar));

            if (IndxPar.DocumentoIndxP == DocumentoAux)
            {
                return 1;
            }
            else
            {
                if (IndxPar.DocumentoIndxP < DocumentoAux)
                {
                    fin = medio - 1;
                }
                else
                {
                    inicio = medio + 1;
                }
            }
        }
        archivoPar.close();
    }
    else
    {
        ifstream archivoImpar;
        archivoImpar.open("ClientesIImpar.inx", ios::binary);
        int medio;
        int inicio = 0;
        archivoImpar.seekg(0, ios::end);
        int fin = (archivoImpar.tellg() / sizeof(IndexPar) - 1);

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            archivoImpar.seekg(medio * sizeof(IndxPar));
            archivoImpar.read((char *)&IndxPar, sizeof(IndxPar));

            if (IndxPar.DocumentoIndxP == DocumentoAux)
            {
                return 1;
            }
            else
            {
                if (IndxPar.DocumentoIndxP < DocumentoAux)
                {
                    fin = medio - 1;
                }
                else
                {
                    inicio = medio + 1;
                }
            }
        }
        archivoImpar.close();
    }

    return 0;
}

void Ordenar_IndicePar()
{

    struct IndexPar Aux;

    //ORDENO INDICE PAR - BURBUJA CORRECTO
    fstream archindiceP;
    archindiceP.open("ClientesIPar.inx", ios::binary | ios::in | ios::out);

    ifstream archCliente;
    archCliente.open("Clientes.dat", ios::binary);
    archCliente.seekg(0, ios::end);

    int pos = archCliente.tellg();
    archCliente.close();

    int ielementos = pos / sizeof(Persona);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            archindiceP.seekg(j * sizeof(IndxPar), ios::beg);
            archindiceP.read((char *)&Aux, sizeof(IndxPar));
            archindiceP.read((char *)&IndxPar, sizeof(IndxPar));

            if (Aux.DocumentoIndxP < IndxPar.DocumentoIndxP)
            {
                archindiceP.seekp(j * sizeof(IndxPar));
                archindiceP.write((char *)&IndxPar, sizeof(IndxPar));
                archindiceP.write((char *)&Aux, sizeof(IndxPar));
            }
        }
    }

    archindiceP.close();
}

void Ordenar_IndiceImpar()
{
    struct IndexImpar Aux;

    //ORDENO INDICE PAR - BURBUJA CORRECTO
    fstream archindiceI;
    archindiceI.open("ClientesIImpar.inx", ios::binary | ios::in | ios::out);

    ifstream archcliente;
    archcliente.open("Clientes.dat", ios::binary);
    archcliente.seekg(0, ios::end);

    int pos = archcliente.tellg();
    archcliente.close();

    int ielementos = pos / sizeof(Persona);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            archindiceI.seekg(j * sizeof(IndxImpar), ios::beg);
            archindiceI.read((char *)&Aux, sizeof(IndxImpar));
            archindiceI.read((char *)&IndxImpar, sizeof(IndxImpar));

            if (Aux.DocumentoIndxI < IndxImpar.DocumentoIndxI)
            {
                archindiceI.seekp(j * sizeof(IndxImpar));
                archindiceI.write((char *)&IndxImpar, sizeof(IndxImpar));
                archindiceI.write((char *)&Aux, sizeof(IndxImpar));
            }
        }
    }

    archindiceI.close();
}

void BuscarCliente()
{
    long long DocumentoAuxBuscado = 0;

    cout << "Ingrese el Documento a buscar: ";
    cin >> DocumentoAuxBuscado;
    fflush(stdin);
    cout << endl;

    if (DocumentoAuxBuscado % 2 == 0)
    {
        //BUSCO EN EL INDICE PAR POR BUSQUEDA BINARIA

        ifstream IndxEntregas;
        IndxEntregas.open("ClientesIPar.inx", ios::binary | ios::in);

        ifstream archivoDatos;
        archivoDatos.open("Clientes.dat", ios::binary);
        archivoDatos.seekg(0, ios::end);
        int posicion = archivoDatos.tellg();
        int fin = (posicion / sizeof(Cliente)) - 1;
        archivoDatos.close();

        int n;
        int medio;
        int inicio = 0;
        int encontrado = 0;

        while (inicio <= fin)
        {

            medio = (fin + inicio) / 2;

            // Posiciono en el medio del archivo
            IndxEntregas.seekg(medio * sizeof(IndxPar));
            IndxEntregas.read((char *)&IndxPar, sizeof(IndxPar));

            if (IndxPar.DocumentoIndxP == DocumentoAuxBuscado)
            {
                // Muestro los datos de las entregas.
                ifstream archivoEntregas;
                archivoEntregas.open("Clientes.dat", ios::binary);
                archivoEntregas.seekg(IndxPar.posicion);
                archivoEntregas.read((char *)&Cliente, sizeof(Cliente));

                cout << "Cliente encontrado!";
                cout << endl;
                cout << "Datos del cliente: ";
                cout << endl;
                cout << "Documento: " << Cliente.Documento;
                cout << endl;
                cout << "Nombre: " << Cliente.Nombre;
                cout << endl;
                cout << "Apellido: " << Cliente.Apellido;
                cout << endl;
                cout << "Edad: " << Cliente.Edad;
                cout << endl;
                cout << "Domicilio: " << Cliente.Domicilio;
                cout << endl;
                cout << "Localidad: " << Cliente.Localidad;
                cout << endl;
                cout << "Producto: " << Cliente.Producto;
                cout << endl;
                cout << "Precio: " << Cliente.Precio;
                cout << endl;
                cout << endl;

                encontrado = 1;
                fin = -1;
            }
            else
            {
                if (DocumentoAuxBuscado > IndxImpar.DocumentoIndxI)
                    fin = medio - 1;
                else
                    inicio = medio + 1;
            }
        }
        if (encontrado != 1)
        {
            cout << "No se encontro el Documento buscado!" << endl;
        }
        IndxEntregas.close();
    }
    else
    {
        //BUSCO EN EL INDICE IMPAR
        ifstream IndxEntregas;
        IndxEntregas.open("ClientesIImpar.inx", ios::binary | ios::in);

        ifstream archivoDatos;
        archivoDatos.open("Clientes.dat", ios::binary);
        archivoDatos.seekg(0, ios::end);
        int posicion = archivoDatos.tellg();
        int fin = (posicion / sizeof(Cliente)) - 1;
        archivoDatos.close();

        int n;
        int medio;
        int inicio = 0;
        int encontrado = 0;

        while (inicio <= fin)
        {

            medio = (fin + inicio) / 2;

            // Posiciono en el medio del archivo
            IndxEntregas.seekg(medio * sizeof(IndxImpar));
            IndxEntregas.read((char *)&IndxImpar, sizeof(IndxImpar));

            if (IndxImpar.DocumentoIndxI == DocumentoAuxBuscado)
            {
                // Muestro los datos del cliente.
                ifstream archivoEntregas;
                archivoEntregas.open("Clientes.dat", ios::binary);
                archivoEntregas.seekg(IndxImpar.posicion);
                archivoEntregas.read((char *)&Cliente, sizeof(Cliente));

                cout << "Cliente encontrado!" << endl;
                cout << "Datos del cliente: " << endl;
                cout << "Documento: " << Cliente.Documento << endl;
                cout << "Nombre: " << Cliente.Nombre << endl;
                cout << "Apellido: " << Cliente.Apellido << endl;
                cout << "Edad: " << Cliente.Edad << endl;
                cout << "Domicilio: " << Cliente.Domicilio << endl;
                cout << "Localidad: " << Cliente.Localidad << endl;
                cout << "Producto: " << Cliente.Producto << endl;
                cout << "Precio: " << Cliente.Precio << endl;
                cout << endl;

                encontrado = 1;
                fin = -1;
            }
            else
            {
                if (DocumentoAuxBuscado > IndxImpar.DocumentoIndxI)
                    fin = medio - 1;
                else
                    inicio = medio + 1;
            }
        }
        if (encontrado != 1)
        {
            cout << "No se encontro el Documento buscado!" << endl;
        }
        IndxEntregas.close();
    }
}

void listarIndicePar()
{

    ifstream archivo;
    archivo.open("ClientesIPar.inx", ios::binary);
    int i = 1;
    while (archivo.read((char *)&IndxPar, sizeof(IndxPar)))
    {
        if (!archivo.eof())
        {
            cout << "Cuil " << i << ": " << IndxPar.DocumentoIndxP;
            cout << endl;
            i++;
        }
    }
    archivo.close();
}

void listarIndiceImpar()
{

    ifstream archivo;
    archivo.open("ClientesIImpar.inx", ios::binary);
    int i = 1;
    while (archivo.read((char *)&IndxImpar, sizeof(IndxImpar)))
    {
        if (!archivo.eof())
        {

            cout << "Documento: " << IndxImpar.DocumentoIndxI;
            cout << endl;
            i++;
        }
    }
    archivo.close();
}