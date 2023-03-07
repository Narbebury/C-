#include <iostream>
#include <cstring>
#include "HeaderF(Libreria).h"

using namespace std;

const char *RecommendMeAFood(char firstLetter);

int main()
{
    cout << "Today I'll eat " << RecommendMeAFood('a');
}

