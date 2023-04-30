#ifndef NODE_H
#define NODE_H


class Node {
private:
    Node() = delete; 
public:
    int key;
    Node* next;
    Node(int new_key);
    void display();
};

#endif