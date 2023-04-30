#include "stack.h"


Stack::Stack() {
    head = nullptr;
}

bool Stack::empty() {
    return head == nullptr;
}

void Stack::push(int new_key) {
    Node* new_node = new Node(new_key);
    new_node->next = head;
    head = new_node;
}

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

int Stack::peek() {
    if (empty()) {
        return 0;
    }
    return head->key;
}