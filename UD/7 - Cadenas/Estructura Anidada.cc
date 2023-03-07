#include <stdio.h>

struct infoDireccion
{
    char Calle[40];
    int Numero;
    char Estado[40];
    char Codigopostal[6];
};

struct infoUsuario
{
    char Nombre[40];
    char Apellido[40];
    struct infoDireccion dir;
    char Telefono[15];
};

int main()
{
    struct infoUsuario maria={"Maria","Sosa",{"Avenida Cors",2045,"Buenos Aires","7900"},"223-645-2019"};

    printf("Usuario: %s %s\n",maria.Apellido,maria.Nombre);
    
    printf("Direccion: %s %d\nEstado: %s\n",maria.dir.Calle,maria.dir.Numero,maria.dir.Estado);

    printf("Codigo Postal: %s",maria.dir.Codigopostal);
    return 0;
}