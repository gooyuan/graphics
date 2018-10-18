
#include "ConstructorVerify.h"
#include "CircularQueue.h"
#include <stdio.h>
#include <iostream> // cout
using namespace std;

int main(int argc, char const *argv[])
{
    /* code */

    // ConstructorVerify cos(5,2,3);
    
    // int matrix[3][3] = {1,2,3,4,5,6, 7,8,9};
    // std::cout << "start: " << std::endl;
    // int (*ptr)[3] = matrix;
    // cos.spiralOrder(matrix, 3, 3);

    MyCircularQueue* obj = myCircularQueueCreate(3);
    printf("insert %d\n", myCircularQueueEnQueue(obj,6));
    printf("last %d\n", myCircularQueueRear(obj));
    printf("last %d\n", myCircularQueueRear(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("insert %d\n", myCircularQueueEnQueue(obj,5));
    printf("last %d\n", myCircularQueueRear(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("front %d\n", myCircularQueueFront(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("isFull %d\n", myCircularQueueIsFull(obj));
    printf("front %d\n", myCircularQueueFront(obj));
    printf("front %d\n", myCircularQueueFront(obj));
    printf("insert %d\n", myCircularQueueEnQueue(obj,6));
    printf("isFull %d\n", myCircularQueueIsFull(obj));
    printf("front %d\n", myCircularQueueFront(obj));
    printf("last %d\n", myCircularQueueRear(obj));
    printf("insert %d\n", myCircularQueueEnQueue(obj,6));
    printf("last %d\n", myCircularQueueRear(obj));
    printf("last %d\n", myCircularQueueRear(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("insert %d\n", myCircularQueueEnQueue(obj,5));
    printf("last %d\n", myCircularQueueRear(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("front %d\n", myCircularQueueFront(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("delete %d\n", myCircularQueueDeQueue(obj));
    printf("isFull %d\n", myCircularQueueIsFull(obj));
    printf("front %d\n", myCircularQueueFront(obj));
    printf("front %d\n", myCircularQueueFront(obj));
    printf("insert %d\n", myCircularQueueEnQueue(obj,6));
    printf("isFull %d\n", myCircularQueueIsFull(obj));
    printf("front %d\n", myCircularQueueFront(obj));
    myCircularQueueFree(obj);
    return 0;
}
