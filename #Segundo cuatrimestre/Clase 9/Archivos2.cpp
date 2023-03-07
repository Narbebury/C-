
using namespace std;

#include <iostream>
#include <fstream>

main()
{
   int num1, num2;
   cout <<"Ingrese desde hasta:";
   cin >> num1 >> num2;
   cout << endl;

   //Archivos
   ofstream archivo;
   archivo.open("NumerosB.txt", ios::app);
   
   for (int i = num1; i < num2+1; i++)
   {
       archivo << i <<endl;
   }
   
   archivo.close();

}