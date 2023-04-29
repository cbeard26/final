#ifndef STACK_H
#define STACK_H

#include "node.h"

class Stack {
private:
    Node* head;
public:
    Stack();
    bool empty();
    void push(int new_key);
    int peek();
    int pop();
};

#endif