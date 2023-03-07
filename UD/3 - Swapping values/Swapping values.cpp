#include <iostream>
using namespace std;

int main()
{
    int num1 = 1;
    int num2 = 2;
    int hold;

    cout << "Before change" << endl;
    cout << "Num1 = " << num1 << endl;
    cout << "Num2 = " << num2;
    cout << endl<<endl;

    hold = num1;
    num1 = num2;
    num2 = hold;

    cout << "After change" << endl;
    cout << "Num1 = " << num1 << endl;
    cout << "Num2 = " << num2;

    cout << endl<<endl;
    cout<<"Other form is using swap function: "<<endl;
    int num3 = 30, num4 = 40;
    cout<<"Num3 = "<<num3<<endl;
    cout<<"Num4 = "<<num4<<endl;
    swap(num3,num4);//change values between num3 and num4
    cout << endl;
    cout<<"Num3 = "<<num3<<endl;
    cout<<"Num4 = "<<num4<<endl;



}