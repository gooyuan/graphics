
#ifndef CIRCULAR_QUEUE
#define CIRCULAR_QUEUE

#include <stdio.h>
#include <stdlib.h>

typedef struct MyCircularQueue CircularQueue;
typedef struct MyCircularQueue{
    int value;
    int index;
    CircularQueue *next;
    CircularQueue *pre;
}*Node;

static Node *header, *end, *origin;
static bool isEmpty=true, isFull = false;
static int count;
/** Initialize your data structure here. Set the size of the queue to be k. */
MyCircularQueue* myCircularQueueCreate(int k) {
    origin = header = end = (Node*)malloc(k * sizeof(Node));
    count = k;
    for(int i=0; i<k; i++){
        // MyCircularQueue node;
        // *(header + i) = node;
        header[i] = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
        if(i>0){
            header[i] -> index = i+1;
            header[i-1]->next = header[i];
            header[i]-> pre = header[i -1];
        }
    }
    header[0]->pre = header[k-1];
    header[k-1]->next = header[0];
    return header[0];
}

/** Insert an element into the circular queue. Return true if the operation is successful. */
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if(!isFull){
        (*end)->value = value;
        end = &((*end)->next);
        isEmpty = false;
        if((*end)->index == (*header)->index) isFull = true;
        return true;
    }
    return false;
}

/** Delete an element from the circular queue. Return true if the operation is successful. */
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if(!isEmpty){
        header = &((*header)-> next);
        isFull = false;
        if((*end)->index == (*header)->index){
            isEmpty = true;
        }
        return true;
    }
    
    return false;
}

/** Get the front item from the queue. */
int myCircularQueueFront(MyCircularQueue* obj) {
    return isEmpty ? -1 : (*header)->value;
}

/** Get the last item from the queue. */
int myCircularQueueRear(MyCircularQueue* obj) {
    return isEmpty ? -1 : ((Node)(*end)->pre)->value;
}

/** Checks whether the circular queue is empty or not. */
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return isEmpty;
}

/** Checks whether the circular queue is full or not. */
bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return isFull;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    Node next = obj->next;
    free(obj);
    int index = 0;
    while(index < count){
        obj = next;
        next = next->next;
        free(obj);
        index++;
    }
    free(origin);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * struct MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 * bool param_2 = myCircularQueueDeQueue(obj);
 * int param_3 = myCircularQueueFront(obj);
 * int param_4 = myCircularQueueRear(obj);
 * bool param_5 = myCircularQueueIsEmpty(obj);
 * bool param_6 = myCircularQueueIsFull(obj);
 * myCircularQueueFree(obj);
 */

#endif