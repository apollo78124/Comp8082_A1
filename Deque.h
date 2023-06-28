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
    explicit Queue(int s) {
        N = s;
        front = 0;
        back = N-1;
        vector<Object> tempVec(N);
        qu1 = tempVec;
    }

    Queue () = default;
    ~Queue() = default;
    void enque(Object obj) {

        if (full() == true) {
            return;
        }

        if (back  >= N - 1 ) {
            back = 0;
            qu1[back] = obj;
        } else {
            back++;
            qu1[back] = obj;
        }
    }
    Object deque() {
        if (empty()) {
            return Object{};
        }
        else  {
            if (front >= N - 1) {
                front = 0;
                return qu1[N - 1];
            } else {
                front++;
                return qu1[front - 1];
            }
        }


    }

    bool empty() {
        if (front == 0) {
            if (back == N-1) {
                return true;
            } else {
                return false;
            }
        } else {
            if (front - 1 == back) {
                return true;
            } else {
                return false;
            }
        }
    }
    bool full() {

        if (back  >= N - 1) {
            if (front == 1) {
                return true;
            } else {
                return false;
            }
        } else  {
            if (back + 2 == front) {
                return true;
            } else {
                return false;
            }
        }
    }
    string print() {
        string printer = "";
        stringstream ss;
            for (int i = 0; i < qu1.size(); i++) {
                ss << qu1[i];
                ss << " ";
            }
        printer = ss.str();
        return printer;
    }
    // this function will return the underlying array used for storing the queue data and will be used to grade the
    // implementation.
    vector<Object> debugGetArray() {
        return qu1;
    }

private:
    vector<Object> qu1;
    int front;
    int back;
    int N;
};

#endif //DEQUE_H
