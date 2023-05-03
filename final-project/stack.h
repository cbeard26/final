#ifndef STACK_H
#define STACK_H

#include "node.h"

/**
 * @brief stores node objects in a first-in-last-out manner
*/
class Stack {
private:
    Node* head; // pointer to top node of the stack
public:
    Stack();
    bool empty();
    void push(int);
    int peek();
    int pop();
};

#endif