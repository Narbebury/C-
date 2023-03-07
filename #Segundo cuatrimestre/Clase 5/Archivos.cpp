#include <iostream>
using namespace std;

main()
{
   struct reg
   {
       int nro_prod;
       char descrp[30];
       int cantidad;
       float precio;
       char garantia;
   }Registro;
   
   long int dir_fisica, dir_logica;
   //dir_fisica = dir_logica * sizeof(Registro);

   cout << "Long registro: " << sizeof(Registro) << endl << endl;

   cout << "Long prod: " << sizeof(Registro.nro_prod) << endl << endl;
   cout << "Long descrp: " << sizeof(Registro.descrp) << endl;
   cout << "Long cant: " << sizeof(Registro.cantidad) << endl;
   cout << "Long precio: " << sizeof(Registro.precio) << endl;
   cout << "Long garant: " << sizeof(Registro.garantia) << endl << endl;
   
   cout << "Long campos :" << sizeof(Registro.nro_prod) + sizeof(Registro.descrp) + sizeof(Registro.cantidad) + sizeof(Registro.precio) + sizeof(Registro.garantia) << endl << endl;

   for (int i = 0; i < 5; i++)
   {
    dir_logica = i;
    cout << "Dir log" << i << ": Dir Fisica: " << dir_logica * sizeof(Registro) << endl;
    }

}
  
