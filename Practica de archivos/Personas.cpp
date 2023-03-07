/*Programa para dar de alta clientes:
1 alta - validar
2 buscar persona
3 generar indice.
4 listar personas
5 listar indices par o impar*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Defino las estructuras necesarias para la ejecución del programa.
struct persona
{
    char Nombre[30];
    char Apellido[30];
    int Edad;
    long long Documento;
    long long Cuil;
    char Direccion[30];
};

struct indxP
{
    long long DocumentoPar;
    int posicion;
};

struct indxI
{
    long long DocumentoImpar;
    int posicion;
};

struct persona Persona;
struct indxP IndicePar;
struct indxI IndiceImpar;

// Defino los prototipos de las funciones.
void AltaCliente();
int Valida(long long);
void OrdenoIndicePar();
void OrdenoIndiceImpar();
void BuscarCliente();
void ListarClientes();
void ListarIndices();

int main()
{
    int op = 0;
    int op2 = 0;

    do
    {

        cout << "MENU";
        cout << endl;
        cout << "1 - Alta cliente";
        cout << endl;
        cout << "2 - Buscar cliente";
        cout << endl;
        cout << "3 - Listar clientes";
        cout << endl;
        cout << "4 - Listar indices de clientes";
        cout << endl;
        cout << "5 - Salir";
        cout << endl;
        cin >> op;

        switch (op)
        {
        case 1:
            AltaCliente();
            break;

        case 2:
            BuscarCliente();
            break;

        case 3:
            ListarClientes();
            break;

        case 4:
            ListarIndices();
            break;

        case 5:

            cout << "Esta seguro que quiere salir ?" << endl;
            cout << "1 - Si";
            cout << endl;
            cout << "2 - No";
            cout << endl;
            cin >> op2;

            if (op2 == 1)
            {
                cout << "Hasta luego...";
            }
            else
            {
                return main();
            }
            break;

        default:
            cout << "Ingrese una opcion correcta";
            cout << endl;
            return main();
            break;
        }

    } while (op = !5);
}

void AltaCliente()
{
    ofstream archCliente;
    archCliente.open("Cliente.dat", ios::binary | ios::app | ios::ate);

    int valido = -1;

    cout << "Ingrese el Documento: ";
    cin >> Persona.Documento;
    cout << endl;

    valido = Valida(Persona.Documento);

    if (valido == 1)
    {
        cout << "El Documento ingresado ya existe";
        int op4 = 0;
        cout << "Quiere cargar otra persona?";
        cout << endl;
        cout << "1 - Si";
        cout << endl;
        cout << "2 - No";
        cout << endl;
        cin>> op4;

        if (op4 == 1)
        {
            return AltaCliente();
        }
        else
        {
            cout << "Hasta luego..";
        }
    }
    else
    {
        fflush(stdin);
        cout << "Ingrese el Nombre: ";
        cin.getline(Persona.Nombre, 30);
        cout << endl;

        cout << "Ingrese el Apellido: ";
        cin.getline(Persona.Apellido, 30);
        cout << endl;

        cout << "Ingrese la Edad: ";
        cin >> Persona.Edad;

        cout << "Ingrese el Cuil: ";
        cin >> Persona.Cuil;
        cout << endl;
        fflush(stdin);

        cout << "Ingrese la Direccion: ";
        cin.getline(Persona.Direccion, 30);
        cout << endl;
        fflush(stdin);

        // GUARDO DATOS EN ARCHIVO MAESTRO.
        archCliente.write((char *)&Persona, sizeof(persona));
        

        // Evaluo si el documento ingresado es par o impar para cargarlo en su respectivo indice.
        if (Persona.Documento % 2 == 0)
        {
            ofstream archIndicePar;
            archIndicePar.open("ClientesIPar.inx", ios::binary | ios::app | ios::ate);
            IndicePar.posicion = archCliente.tellp();
            IndicePar.posicion = IndicePar.posicion - sizeof(Persona);
            IndicePar.DocumentoPar = Persona.Documento;
            archIndicePar.write((char *)&IndicePar, sizeof(IndicePar));
            archIndicePar.close();
        }
        else
        {
            ofstream archIndiceImpar;
            archIndiceImpar.open("ClientesImpar.inx", ios::binary | ios::app | ios::ate);
            IndiceImpar.posicion = archCliente.tellp();
            IndiceImpar.posicion = IndicePar.posicion - sizeof(Persona);
            IndiceImpar.DocumentoImpar = Persona.Documento;
            archIndiceImpar.write((char *)&IndiceImpar, sizeof(IndiceImpar));
            archIndiceImpar.close();
        }

        // Luego de cargar los datos y el indice los ordeno.
        archCliente.close();
        OrdenoIndicePar();
        OrdenoIndiceImpar();
    }
}

int Valida(long long DocumentoAux)
{
    // VALIDACIÓN POR BUSQUEDA BINARIA PARA INDICE PAR
    if (Persona.Documento % 2 == 0)
    {
        ifstream archivoP;
        archivoP.open("ClientesIPar.inx", ios::binary);
        int medio;
        int inicio = 0;
        archivoP.seekg(0, ios::end);
        int fin = (archivoP.tellg() / sizeof(indxP) - 1);

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            archivoP.seekg(medio * sizeof(indxP));
            archivoP.read((char *)&IndicePar, sizeof(indxP));

            if (IndicePar.DocumentoPar == DocumentoAux)
            {
                return 1;
            }
            else
            {
                if (IndicePar.DocumentoPar < DocumentoAux)
                {
                    fin = medio - 1;
                }
                else
                {
                    inicio = medio + 1;
                }
            }
        }
        archivoP.close();
    }
    else // VALIDACIÓN POR BUSQUEDA BINARIA PARA INDICE IMPAR
    {
        ifstream archivoIm;
        archivoIm.open("ClientesImpar.inx", ios::binary);
        int medio;
        int inicio = 0;
        archivoIm.seekg(0, ios::end);
        int fin = (archivoIm.tellg() / sizeof(indxI) - 1);

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            archivoIm.seekg(medio * sizeof(indxI));
            archivoIm.read((char *)&IndiceImpar, sizeof(indxI));

            if (IndiceImpar.DocumentoImpar == DocumentoAux)
            {
                return 1;
            }
            else
            {
                if (IndiceImpar.DocumentoImpar < DocumentoAux)
                {
                    fin = medio - 1;
                }
                else
                {
                    inicio = medio + 1;
                }
            }
        }
        archivoIm.close();
    }

    return 0;
}

void OrdenoIndicePar()
{
    fstream Iarchivo;
    Iarchivo.open("ClientesIPar.inx", ios::binary | ios::in | ios::out);

    ifstream archivoM;
    archivoM.open("Cliente.dat", ios::binary);
    archivoM.seekg(0, ios::end);
    archivoM.close();

    struct indxP IPAuxiliar;

    int pos = archivoM.tellg();
    int ielementos = pos / sizeof(persona);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            Iarchivo.seekg(j * sizeof(IndicePar), ios::beg);
            Iarchivo.read((char *)&IPAuxiliar, sizeof(IndicePar));
            Iarchivo.read((char *)&IndicePar, sizeof(IndicePar));

            if (IPAuxiliar.DocumentoPar < IndicePar.DocumentoPar)
            {
                Iarchivo.seekp(j * sizeof(IndicePar));
                Iarchivo.write((char *)&IndicePar, sizeof(IndicePar));
                Iarchivo.write((char *)&IPAuxiliar, sizeof(IndicePar));
            }
        }
    }
    Iarchivo.close();
}

void OrdenoIndiceImpar()
{
    fstream Iarchivoimp;
    Iarchivoimp.open("ClientesImpar.inx", ios::binary | ios::in | ios::out);

    ifstream archivoM;
    archivoM.open("Cliente.dat", ios::binary);
    archivoM.seekg(0, ios::end);
    archivoM.close();

    struct indxI IImpAuxiliar;

    int pos = archivoM.tellg();
    int ielementos = pos / sizeof(persona);

    for (int i = 1; i < ielementos; i++)
    {
        for (int j = 0; j < ielementos; j++)
        {
            Iarchivoimp.seekg(j * sizeof(IndiceImpar), ios::beg);
            Iarchivoimp.read((char *)&IImpAuxiliar, sizeof(IndiceImpar));
            Iarchivoimp.read((char *)&IndiceImpar, sizeof(IndiceImpar));

            if (IImpAuxiliar.DocumentoImpar < IndiceImpar.DocumentoImpar)
            {
                Iarchivoimp.seekp(j * sizeof(IndiceImpar));
                Iarchivoimp.write((char *)&IndiceImpar, sizeof(IndiceImpar));
                Iarchivoimp.write((char *)&IImpAuxiliar, sizeof(IndiceImpar));
            }
        }
    }
    Iarchivoimp.close();
}

void BuscarCliente()
{
    long long DocumentoAux = 0;
    cout << "Ingrese el Documento del cliente: ";
    cin >> DocumentoAux;
    fflush(stdin);
    cout << endl;

    if (Persona.Documento % 2 == 0)
    {
        ifstream archivodatos;
        archivodatos.open("clientes.dat",ios::binary);
        archivodatos.seekg(0, ios::end);
        int posicion = archivodatos.tellg();
        int fin = (posicion / sizeof(indxP) - 1);

        archivodatos.close();

        ifstream archivoP;
        archivoP.open("ClientesIPar.inx", ios::binary|ios::in);
        int medio;
        int inicio = 0;
        int encontrado = 0;

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            archivoP.seekg(medio * sizeof(Persona));
            archivoP.read((char *)&IndicePar, sizeof(IndicePar));

            if (IndicePar.DocumentoPar == DocumentoAux)
            {

                ifstream DatosClientes;
                DatosClientes.open("Cliente.dat", ios::binary);
                DatosClientes.seekg(IndicePar.posicion);
                DatosClientes.read((char *)&Persona, sizeof(persona));

                cout << "Nombre: " << Persona.Nombre;
                cout << endl;

                cout << "Apellido: " << Persona.Apellido;
                cout << endl;

                cout << "Edad: " << Persona.Edad;
                cout << endl;

                cout << "Documento: " << Persona.Documento;
                cout << endl;

                cout << "Cuil: " << Persona.Cuil;
                cout << endl;

                cout << "Direccion: " << Persona.Direccion;
                cout << endl;

                encontrado = 1;
                fin = -1;
                DatosClientes.close();
            }
            else
            {
                if (DocumentoAux > IndicePar.DocumentoPar)
                {
                    fin = medio - 1;
                }
                else
                {
                    inicio = medio + 1;
                }
            }

            archivoP.close();
        }
    }
    else
    {
        ifstream archivodatosi;
        archivodatosi.open("clientes.dat",ios::binary);
        archivodatosi.seekg(0, ios::end);
        int posicion = archivodatosi.tellg();
        int fin = (posicion / sizeof(indxP) - 1);

        archivodatosi.close();
        ifstream archivoIm;
        archivoIm.open("ClientesImpar.inx", ios::binary);
        int medio;
        int inicio = 0;
        int encontrado = 0;

        while (inicio <= fin)
        {
            medio = (fin + inicio) / 2;
            archivoIm.seekg(medio * sizeof(persona));
            archivoIm.read((char *)&IndiceImpar, sizeof(indxI));

            if (IndiceImpar.DocumentoImpar == DocumentoAux)
            {
                ifstream DatosClientes;
                DatosClientes.open("Cliente.dat", ios::binary);
                DatosClientes.seekg(IndicePar.posicion);
                DatosClientes.read((char *)&Persona, sizeof(persona));

                cout << "Nombre: " << Persona.Nombre;
                cout << endl;

                cout << "Apellido: " << Persona.Apellido;
                cout << endl;

                cout << "Edad: " << Persona.Edad;
                cout << endl;

                cout << "Documento: " << Persona.Documento;
                cout << endl;

                cout << "Cuil: " << Persona.Cuil;
                cout << endl;

                cout << "Direccion: " << Persona.Direccion;
                cout << endl;

                encontrado = 1;
                fin = -1;
                DatosClientes.close();
            }
            else
            {
                if (DocumentoAux > IndiceImpar.DocumentoImpar)
                {
                    fin = medio - 1;
                }
                else
                {
                    inicio = medio + 1;
                }
            }
        }
        archivoIm.close();
    }
}

void ListarClientes()
{

    ifstream client;
    client.open("Cliente.dat", ios::binary);
    int icont = 0;

    while (client.read((char *)&Persona, sizeof(persona)) && !client.eof())
    {
        cout << "Nombre: " << Persona.Nombre;
        cout << endl;

        cout << "Apellido: " << Persona.Apellido;
        cout << endl;

        cout << "Edad: " << Persona.Edad;
        cout << endl;

        cout << "Documento: " << Persona.Documento;
        cout << endl;

        cout << "Cuil: " << Persona.Cuil;
        cout << endl;

        cout << "Direccion: " << Persona.Direccion;
        cout << endl;
        icont++;
    }
    cout << "Total de clientes: " << icont;
    client.close();
}

void ListarIndices()
{
    int op3 = 0;
    cout << "1 - Listar Indices con Documentos Par";
    cout << endl;
    cout << "2 - Listar Indices con Documentos Impar";
    cout << endl;
    cin >> op3;

    if (op3 % 2 == 0)
    {
        ifstream client1;
        client1.open("ClientesIPar.inx", ios::binary);
        int icont = 0;

        while (client1.read((char *)&IndicePar, sizeof(indxP)) && !client1.eof())
        {
            cout << "Documento: " << IndicePar.DocumentoPar;
            cout << endl;
            icont++;
        }
        cout << "Total de clientes: " << icont;
        client1.close();
    }
    else
    {
        ifstream client2;
        client2.open("ClientesImpar.inx", ios::binary);
        int icont = 0;

        while (client2.read((char *)&IndiceImpar, sizeof(indxI)) && !client2.eof())
        {
            cout << "Documento: " << IndiceImpar.DocumentoImpar;
            cout << endl;
            icont++;
        }
        cout << "Total de clientes: " << icont;
        client2.close();
    }
}