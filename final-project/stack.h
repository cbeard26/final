#ifndef STACK_H
#define STACK_H

#include "node.h"

class Stack {
private:
    Node* head;
public:
    Stack();
    bool empty();
    void push(int);
    int peek();
    int pop();
};

#endif