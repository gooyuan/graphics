
#include "ConstructorVerify.h"
#include <iostream> // cout
using namespace std;

int main(int argc, char const *argv[])
{
    /* code */

    ConstructorVerify cos(5,2,3);
    
    cout << cos._x << "," << cos._y << "," << cos._z <<endl;

    return 0;
}
