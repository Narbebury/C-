#include <iostream>
#include <string>
using namespace std;


char *matriz[3][3];


void Relleno(); // Cargo la Matriz con valores Pre determinados ( * )
void Mostrar(); // Muestro la Matriz en cada iteracion
void Jugada(); // Jugada del usuario
void Jugada_Maquina(); // Jugada de la maquina
bool Verificacion_de_posicion(int , int ); // Verifica si la posicion esta ocupada o no
bool Verificacion_de_ganador(char); // Verifica si alguno de los jugadores (Usuario o Maquina) ganó 


int main()
{
	cout << ("Bienvendos") << endl << endl;

	Relleno();

	return 1;
}

void Relleno(){
	char relleno = '*';
	for (int x = 0; x < 3; ++x) 
	{
			for (int y = 0; y < 3; ++y) 
			{
				matriz[y][x] = &relleno;
			}
	}
	Mostrar();
}

void Mostrar(){

		cout << endl<<endl <<"\t|   1 	|   2 	|   3   | " << endl; 
		cout << "----------------------------------" << endl;
		cout << "    1   |   " << *matriz[0][0] << " 	|   " << *matriz[0][1] << " 	|   " << *matriz[0][2] <<"   |   "<< endl; 
		cout << "----------------------------------" << endl;
		cout << "    2   |   " << *matriz[1][0] << " 	|   " << *matriz[1][1] << " 	|   " << *matriz[1][2] <<"   |   "<< endl;
		cout << "----------------------------------" << endl;
		cout << "    3   |   " << *matriz[2][0] << " 	|   " << *matriz[2][1] << " 	|   " << *matriz[2][2] <<"   |   "<<endl;
		cout << endl; 

	Jugada();
}

void Jugada(){
	int x, y;
	char Jugador = 'X';

	cout << ("Ingrese la posicion en la fila: ");
	cin >> x;
	cout << ("Ingrese la posicion en la columna: ");
	cin >> y;

// Ajusto a la posicion REAL de la matriz (x,y), Ya que esta se muestra al usuario iniciando desde el 1, y no desde el 0. 
	y = y - 1;
	x = x - 1;

	if (Verificacion_de_posicion(x,y) == true)
	{
		matriz[x][y] = &Jugador;	
		if (Verificacion_de_ganador(Jugador) == false)
		{	
			Jugada_Maquina();
			Mostrar();
		}else{
			cout << ("	Ganaste	") << endl << endl;
			system("cls");
			main();
		}
	}
	else
	{
		cout << "Esa casilla se encuentra marcada" <<endl;
		cout << "Intente nuevamente" <<endl;
		Jugada();
	}
	
}

bool Verificacion_de_posicion(int x, int y){
	
	if (*matriz[x][y] == '*')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Jugada_Maquina(){

int x = 0 + rand() % 3;
int y = 0 + rand() % 3;
char Maquina = 'O';
	
	if (Verificacion_de_posicion(x,y) == true)
	{
			if (Verificacion_de_ganador(Maquina) == false)
			{
				matriz[x][y] = &Maquina;
				Mostrar();
			}else{  cout << "Gano la Maquina  " << endl; system("cls"); main();}
	}else{ Jugada_Maquina(); }
}

bool Verificacion_de_ganador(char Marca){

bool bandera=false;

	if ( *matriz[0][0] == *matriz[0][1] && *matriz[0][1] == *matriz[0][2] && *matriz[0][0] == Marca ) // linea superior horizontal
	{	
		bandera = true;
	}
	else if ( *matriz[1][0] == *matriz[1][1] && *matriz[1][0] == *matriz[1][2] && *matriz[1][0] == Marca) // linea media horizontal
	{
		bandera = true;
	}
	else if ( *matriz[2][0] == *matriz[2][1] && *matriz[2][1] == *matriz[2][2] && *matriz[2][0] == Marca) // linea inferior horizontal
	{
		bandera = true;
	}
	else if ( *matriz[0][0] == *matriz[1][0] && *matriz[1][0] == *matriz[2][0] && *matriz[0][0] == Marca) // linea izquierda vertical
	{
		bandera = true;
	}
	else if ( *matriz[0][1] == *matriz[1][1] && *matriz[1][1] == *matriz[2][1] && *matriz[0][1] == Marca) // Linea medio vertical
	{
		bandera = true;
	}
	else if ( *matriz[0][2] == *matriz[1][2] && *matriz[1][2] == *matriz[2][2] && *matriz[0][2] == Marca) // Linea derecha vertical
	{
		bandera = true;
	}
	else if ( *matriz[0][0] == *matriz[1][1] && *matriz[1][1] == *matriz[2][2] && *matriz[0][0] == Marca) // Linea diagonal izquierda superior a derecha inferior
	{
		bandera = true;
	}
	else if ( *matriz[0][2] == *matriz[1][1] && *matriz[1][1] == *matriz[2][0] && *matriz[0][2] == Marca) // Linea diagonal izquierda inferior a derecha superior
	{
		bandera = true;
	}



	return bandera;
}
