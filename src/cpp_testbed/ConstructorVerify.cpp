
#include "ConstructorVerify.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
enum{
    right,
    down,
    left,
    up
};

int* ConstructorVerify::spiralOrder(int matrix[3][3], int matrixRowSize, int matrixColSize) {
    int status[matrixRowSize][matrixColSize];
    int row=0, col=0, index=0, rowEnd = matrixRowSize -1, colEnd = matrixColSize -1;
    for(; row < matrixRowSize; row++){
        col = 0;
        for(;col<matrixColSize; col++){
            status[row][col] = 1;
        }
    }
    int d = right;
    int size = matrixRowSize * matrixColSize;
    int *result = (int*)malloc(size * sizeof(int));
    row=col=0;
    // 每次移动最多有两个方向, 所以, 可以按迷宫来的方式来判断
    while(index < size){
        printf("%d,%d\n", row, col);
        if(row > matrixRowSize -1 || col > matrixColSize -1 || row < 0 || col < 0) {
            std::cout << "index: " << index << std::endl;
            break;
        }
        status[row][col] = 0;
        // printf("%d,%d\n", index, matrix[row][col]);
        result[index] = matrix[row][col];
        // std::cout << "direction: " << d << std::endl;
        switch(d){
            case right:
                col++;
                // 换向, 边界与内部不一样
                if(col == matrixColSize - 1){
                    d = down;
                }else if(!status[row][col]){
                    col--;
                    d = down;
                }
                break;
            case down:
                row++;
                if(row == matrixRowSize -1){
                    d = left;
                }else if(!status[row][col]){
                    --row;
                    d = left;
                }
                break;
            case left:
                --col;
                if(col == 0){
                    d = up;
                }else if(!status[row][col]){
                    col++;
                    d = up;
                }
                break;
            case up:
                row--;
                if(!status[row][col]){
                    row++;
                    d = right;
                }
                break;
        }
    }
    return result;
}
