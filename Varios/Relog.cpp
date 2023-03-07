#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    int seg = 40,minutos = 10, horas = 9;
    bool ciclo = true;

    while (ciclo)
    {
        system("cls");
        cout<<horas<<":"<<minutos<<":"<<seg<<endl;
        Sleep(1000);
        seg++;
        if (seg == 60)
        {
            minutos++;
            seg = 0;
        }
        if (minutos == 60)
        {
            horas++;
            minutos = 0;
        }
        if (horas == 13)
        {
            horas = 1;
            seg = 0;
            minutos = 0;
        }
        
    }
    


    return 0;
}