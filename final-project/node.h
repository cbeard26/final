#ifndef NODE_H
#define NODE_H

/**
 * @brief object that contains a key and a pointer to another node
*/
class Node {
private:
    Node() = delete; // disallows default constructor
public:
    int key; //node's key
    Node* next; // pointer no next node in stack
    Node(int new_key);
};

#endif