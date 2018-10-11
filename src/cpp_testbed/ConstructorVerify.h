
#ifndef CONSTRUCTOR_VERIFY_H
#define CONSTRUCTOR_VERIFY_H

/**
 * 1. 验证 memberwise, bitwise
 *  编译器是如何构建 default constructor的
 *  书上的是伪代码, 既然已经声明了, 肯定得定义
 * 
 * 2. 验证 copy constructor
 */ 
class ConstructorVerify{
    public:
        ConstructorVerify(int x, int y, int z);
        int _x, _y, _z;
        int* spiralOrder(int matrix[3][3], int matrixRowSize, int matrixColSize);

    private:
};

#endif
