
#include "ConstructorVerify.h"
#include <iostream> // cout
using namespace std;

int main(int argc, char const *argv[])
{
    /* code */

    ConstructorVerify cos(5,2,3);
    
    int matrix[3][3] = {1,2,3,4,5,6, 7,8,9};
    std::cout << "start: " << std::endl;
    int (*ptr)[3] = matrix;
    cos.spiralOrder(matrix, 3, 3);

    return 0;
}
