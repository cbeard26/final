#include "node.h"

/**
 * @brief constructor for a node
 * 
 * @param new_key the new node's key
*/
Node::Node(int new_key) {
    key = new_key;
    next = nullptr;
}