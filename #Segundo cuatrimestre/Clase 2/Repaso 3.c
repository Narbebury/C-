/*a) defina una funcion que reciba 2 numeros enteros y muestre el resultado de su producto
b) defina una funcion que reciba 2 numeros enteros , calcule su suma y retorno el valor al MAIN
*/

#include <stdio.h>
//a
void producto(int, int); //PROTOTIPO (DEJA EN CLARO QUE QUEDA Y QUE DEVUELVE LA FUNCIÓN)

//b
int suma (int, int);

main()
{
  //a
  producto(5,6);
  
  //b
  int resultadoFuncion;
  resultadoFuncion = suma(10, 22);
  printf("%i \n", resultadoFuncion);

}
//a
void producto(int a, int b)
{
  printf("%i \n", a * b);
}
//b
int suma (int a, int b)
{
    int resultado = 0;
    resultado = a + b;
    
    return resultado;
}