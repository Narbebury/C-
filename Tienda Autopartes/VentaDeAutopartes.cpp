/*Programa para ventas de autopartes
El siguente programa contara con la venta de autopartes tanto para clientes dados de alta con su DNI (Se aplica descuento) como para clientes que no estan registrados(IDEX APARTE).
Se contará con un menu de inicio el cual nos brindará las opciones de:
1) Venta / Alta (Dentro de podra)
2) Buscar Cliente (Mediante el metódo de busqueda binaria se buscará al cliente por medio de su DNI)
3) Listar Clientes
4) Generar Indice

*********** agregar:: ver ventas totales

*/
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct VentaDeAutopartes
{
    char Nombre[100];
    char Apellido[100];
    long long Documento;
    char Direccion[100];
    char Ciudad[100];
    char Producto[100];
    float Precio;
};

struct indx
{
    long long DocumentoIR;
    int posicion;
};

struct indx2
{
    float Precio;
    int posicion;
};

struct VentaDeAutopartes DatosCliente;
struct indx IndiceClieteRegistrados;
struct indx2 IndiceClieteNoRegistrados;

void AltaVenta();
int Valida(long long DocumentoAUX);
void ListarIndice();
void Ordenar_IndiceRegistrados();
void Buscar();
void VentaNoRegistrado();
// void Ordenar_IndiceNoRegistrados();

int main()
{
    int opcion = 0;
    int opcion2 = 0;
    int EstadoCliente = 0;

    do
    {
        cout << "BIENVENIDO!" << endl;
        cout << "Menu" << endl;
        cout << "1 - Venta" << endl;
        cout << "2 - Buscar Cliente" << endl;
        cout << "3 - Listar Clientes" << endl;
        cout << "4 - Genrar indice" << endl;
        cout << "5 - Salir" << endl;
        cin >> opcion;
        cout << endl;
        fflush(stdin);

        switch (opcion)
        {
        case 1:
            cout << "El cliente esta registrado\1 - Si\2 - No\n";
            if (EstadoCliente == 1)
            {
                AltaVenta();
            }
            else
            {
                VentaNoRegistrado();
            }

            break;

        case 2:
            Buscar();
            break;

        case 3:
            ListarIndice();
            break;
        case 4:
            // Generar_Indice();
            break;

        case 5:
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

void AltaVenta()
{
    int validacion = -1;

    // Defino el archivo Maestro
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("RegistroVentas.dat", ios::binary | ios::app | ios::ate);

    if (ArchivoMaestro.fail())
    {
        cout << "Error al abrir el archivo";
        exit(1);
    }

    cout << "Ingrese el Documento del Cliente: ";
    cin >> DatosCliente.Documento;
    fflush(stdin);

    validacion = Valida(DatosCliente.Documento);

    // Se realiza la validación, si el cliente existe se pregunta si quiere cargar otro, caso contrario se continuará solicitando los datos del cliente
    if (DatosCliente.Documento == 1)
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
            return AltaVenta();
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

        cout << "Ingrese el Apellido: ";
        cin.getline(DatosCliente.Apellido, 100);

        cout << "Ingrese la Direccion: ";
        cin.getline(DatosCliente.Direccion, 100);

        cout << "Ingrese la Ciudad : ";
        cin.getline(DatosCliente.Ciudad, 100);

        cout << "Ingrese el Producto: ";
        cin.getline(DatosCliente.Producto, 100);

        cout << "Ingrese el Precio: ";
        cin >> DatosCliente.Precio;
        fflush(stdin);

        // Guardo los datos ingresados en el archivo Maestro
        ArchivoMaestro.write((char *)&DatosCliente, sizeof(VentaDeAutopartes));

        // Guardo datos en mi indice
        ofstream ArchivoIndiceR;
        ArchivoIndiceR.open("IndxRegistrados.inx", ios::binary | ios::app | ios::ate);

        IndiceClieteRegistrados.posicion = ArchivoMaestro.tellp();
        IndiceClieteRegistrados.posicion = IndiceClieteRegistrados.posicion - sizeof(DatosCliente);
        IndiceClieteRegistrados.DocumentoIR = DatosCliente.Documento;

        ArchivoIndiceR.write((char *)&IndiceClieteRegistrados, sizeof(VentaDeAutopartes));

        // Cierro ambos archivos
        ArchivoIndiceR.close();
        ArchivoMaestro.close();

        Ordenar_IndiceRegistrados();
    }
}

int Valida(long long DocumentoAUX)
{
    ifstream ArchivoIndiceR;
    ArchivoIndiceR.open("IndxRegistrados.inx", ios::binary);
    int medio;
    int inicio = 0;
    ArchivoIndiceR.seekg(0, ios::end);
    int fin = (ArchivoIndiceR.tellg() / sizeof(indx) - 1);

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        ArchivoIndiceR.seekg(medio * sizeof(indx));
        ArchivoIndiceR.read((char *)&IndiceClieteRegistrados, sizeof(indx));

        if (DocumentoAUX == IndiceClieteRegistrados.DocumentoIR)
        {
            return 1;
        }
        else
        {
            if (IndiceClieteRegistrados.DocumentoIR < DocumentoAUX)
            {
                fin = medio - 1;
            }
            else
            {
                inicio = medio + 1;
            }
        }
    }
    ArchivoIndiceR.close();
    return 0;
}

// Funcion para ordenar el indice de registrados mediante metodo Burbuja.
void Ordenar_IndiceRegistrados()
{
    fstream archivoIndxRegistrados;
    archivoIndxRegistrados.open("IndxRegistrados.inx", ios::binary | ios::in | ios::out);

    ifstream ArchivoMaestro;
    ArchivoMaestro.open("RegistroVentas.dat", ios::binary);
    ArchivoMaestro.seekg(0, ios::end);

    struct indx IndiceAux;

    int pos = ArchivoMaestro.tellg();
    ArchivoMaestro.close();
    int Elementos = pos / sizeof(VentaDeAutopartes);

    for (int i = 0; i < Elementos; i++)
    {
        for (int j = 0; j < Elementos; j++)
        {
            archivoIndxRegistrados.seekg(j * sizeof(IndiceClieteRegistrados), ios::beg);
            archivoIndxRegistrados.read((char *)&IndiceAux, sizeof(IndiceClieteRegistrados));
            archivoIndxRegistrados.read((char *)&IndiceClieteRegistrados, sizeof(IndiceClieteRegistrados));

            if (IndiceAux.DocumentoIR < IndiceClieteRegistrados.DocumentoIR)
            {
                archivoIndxRegistrados.seekp(j * sizeof(IndiceClieteRegistrados));
                archivoIndxRegistrados.write((char *)&IndiceClieteRegistrados, sizeof(IndiceClieteRegistrados));
                archivoIndxRegistrados.write((char *)&IndiceAux, sizeof(IndiceClieteRegistrados));
            }
        }
    }
    archivoIndxRegistrados.close();
}

void ListarIndice()
{
    ifstream archivoIndx;
    archivoIndx.open("IndxRegistrados.inx", ios::binary);

    while (archivoIndx.read((char *)&IndiceClieteRegistrados, sizeof(VentaDeAutopartes)))
    {
        cout << "Documento: " << IndiceClieteRegistrados.DocumentoIR << endl;
        cout << "Posicion: " << IndiceClieteRegistrados.posicion << endl;
    }
}

// Busco al cliente realizando el metodo de busqueda Binaria
void Buscar()
{
    long long DocumentoAux = 0;

    cout << "Ingrese el Documento del cliente: ";
    cin >> DocumentoAux;
    cout << endl;

    // Comienza la busqueda Binaria
    ifstream ArchivoRegistrados;
    ArchivoRegistrados.open("IndxRegistrados.inx", ios::binary | ios::in);

    ifstream ArchivoDatos;
    ArchivoDatos.open("RegistroVentas.dat", ios::binary);
    ArchivoDatos.seekg(0, ios::end);

    // Defino variables
    int posicion = ArchivoDatos.tellg();
    int fin = (posicion / sizeof(DatosCliente)) - 1;
    int medio;
    int inicio = 0;
    int encontrado = 0;
    ArchivoDatos.close();

    while (inicio <= fin)
    {
        medio = (fin + inicio) / 2;
        // Me posiciono en el medio del archivo
        ArchivoRegistrados.seekg(medio * sizeof(IndiceClieteRegistrados));
        ArchivoRegistrados.read((char *)&IndiceClieteRegistrados, sizeof(IndiceClieteRegistrados));

        // Si mis Documento coinciden voy a mostrar los datos del cliente
        if (IndiceClieteRegistrados.DocumentoIR == DocumentoAux)
        {
            ifstream ArchivoMaestro;
            ArchivoMaestro.open("RegistroVentas.dat", ios::binary);
            ArchivoMaestro.seekg(IndiceClieteRegistrados.posicion);
            ArchivoMaestro.read((char *)&DatosCliente, sizeof(DatosCliente));

            cout << "Cliente encontrado" << endl;
            cout << " " << DatosCliente.Apellido << " " << DatosCliente.Nombre << endl;
            cout << "Ciudad: " << DatosCliente.Ciudad << endl;
            cout << "Dirreccion: " << DatosCliente.Direccion << endl;
            cout << "Producto: " << DatosCliente.Producto << endl;
            cout << "Precio: " << DatosCliente.Precio << endl;
            cout << endl;
            encontrado = 1;
            fin = -1;
        }
        else
        {
            if (DocumentoAux > IndiceClieteRegistrados.DocumentoIR)
            {
                fin = medio - 1;
            }
            else
            {
                fin = medio + 1;
            }
        }
        if (encontrado != 1)
        {
            cout << "No se encontro el Documento del cliente";
        }
    }
}

void VentaNoRegistrado()
{
    ofstream ArchivoMaestro;
    ArchivoMaestro.open("RegistroVentas.dat", ios::binary | ios::app | ios::ate);

    if (ArchivoMaestro.fail())
    {
        cout << "Error al abrir el archivo";
        exit(1);
    }

    struct Cliente
    {
        char Nombre[100];
        char Apellido[100];
        char Producto[100];
        float Precio;
    } DatosNoRegistrado;

    cout << "Ingrese el Nombre: ";
    cin.getline(DatosNoRegistrado.Nombre, 100);
    cout << "Ingrese el Apellido: ";
    cin.getline(DatosNoRegistrado.Apellido, 100);
    cout << "Ingrese el Producto: ";
    cin.getline(DatosNoRegistrado.Producto, 100);
    cout << "Ingrese el Precio: ";
    cin >> DatosNoRegistrado.Precio;
    cout << endl;

    // Guardo datos en archivo Maestro
    ArchivoMaestro.write((char *)&DatosNoRegistrado, sizeof(Cliente));

    // Guardo datos en indice
    ofstream ArchivoINDICE;
    ArchivoINDICE.open("RegistroVentasNoRegistrados.dat", ios::binary | ios::app | ios::ate);

    IndiceClieteNoRegistrados.posicion = ArchivoMaestro.tellp();
    IndiceClieteNoRegistrados.posicion = IndiceClieteNoRegistrados.posicion - sizeof(DatosNoRegistrado);
    IndiceClieteNoRegistrados.Precio = DatosNoRegistrado.Precio;
    ArchivoINDICE.write((char*)&IndiceClieteNoRegistrados,sizeof(Cliente));

    ArchivoMaestro.close();
    ArchivoINDICE.close();
}