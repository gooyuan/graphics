
#include "ConstructorVerify.h"
/**
 * 1. 验证 memberwise, bitwise
 *  所谓memberwise, bitwise 并不是编译器自动做的? 同样需要程序员人为赋值, 只是将这种操作行为称为memberwise, bitwise
 * 2. 验证 copy constructor
 * 3. member initialization list
 *  member initialization list 被编译器插入在 constructor 实现之前
 */ 

ConstructorVerify::ConstructorVerify(int x, int y, int z) : _y(y), _z(z){
    _x = _y;
    // _x = x;
    // _y = y;
    // _z = z;
}

