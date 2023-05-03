#include "stack.h"

/**
 * @brief default constructor for Stack
*/
Stack::Stack() {
    head = nullptr;
}

/**
 * @brief returns, as bool, whether the stack is empty
 * 
 * @return true if empty, otherwise false
*/
bool Stack::empty() {
    return head == nullptr;
}

/**
 * @brief pushes a new node onto the Stack
 * 
 * @param new_key key of the node to be pushed
*/
void Stack::push(int new_key) {
    Node* new_node = new Node(new_key);
    new_node->next = head;
    head = new_node;
}

/**
 * @brief removes top node from the Stack
 * 
 * @return the key of the node removed from the stack
*/
int Stack::pop() {
    if (empty()) {
        return 0;
    }
    int top_key = head->key;
    Node* top_next = head->next;
    delete head;
    head = top_next;
    return top_key;
}

/**
 * @brief gives the key of the top node of the stack
 * 
 * @return top node's key
*/
int Stack::peek() {
    if (empty()) {
        return 0;
    }
    return head->key;
}