#include <iostream>
#include <cstring>

using namespace std;

const char *RecommendMeAFood(char firstLetter)
{
    if (firstLetter == 'a' || firstLetter == 'A')
    {
        return "Apple";
    }
    else if (firstLetter == 'b' || firstLetter == 'B')
        return "Banana";
    else if (firstLetter == 'c' || firstLetter == 'C')
        return "Chocolate cake";
    else
        return "Pizza";
}