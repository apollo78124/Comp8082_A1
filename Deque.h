// Starter code Deque - Question 2 of Assignment 1
#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <vector>

using namespace std;

template <typename Object>
/**
 * Read this carefully.
 *  The convention you will use in this implementation to prevent headache is that you consider the queue to be empty if
 *   front and back pointers are on top of each other. However, you assume the queue to be full if the front and back
 *    pointers are besides each other (essentially if the front pointer is pointing to the element immediate to the
 *     right of the back pointer. This constraint will force your circular array to signal its full when there are N-1
 *      elements in it but it does not really matter to us in this assignment since this assumption makes your
 *       implementation much easier.
 */
class Queue {
public:
    explicit Queue(int s) {}
    Queue () = default;
    ~Queue() = default;
    void enque(Object obj) {}
    Object deque() {return (Object)0;}
    bool empty() {return true;}
    bool full() {return false;}
    string print() {return "";}
    // this function will return the underlying array used for storing the queue data and will be used to grade the
    // implementation.
    vector<Object> debugGetArray() {return vector<Object>({});}
};

#endif //DEQUE_H
