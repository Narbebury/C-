#include <iostream>

using namespace std;

int main()
{
    //Reference
    string fruit = "Banana";

    //I define &item which use as a variable name for fruit, means the same
    string &item = fruit;
    cout << "Reference: " << item << endl;

    cout << endl;
    //Memory Address:
    cout << "Memory Address: " << &item << endl;
    cout << "Memory Address: " << &fruit << endl;

    //Reference modify the original
    item = "Apple"; //A reference holds a reference to another variable

    //Creating a pointer, variable that sores the memory address as a value.
    string *pointer = &fruit; //A pointer stores the memory value

    cout << "Pointer: " << pointer << endl;

    //Modifying the pointer.
    *pointer = "Something Else";

    cout << "Dereference: " << *pointer << endl; //If i don't print the * it'll give me a memory address

    *pointer = "Hello Word";
    cout<<endl;
    cout <<*pointer;

    return 0;
}