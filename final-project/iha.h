#ifndef IHA_H
#define IHA_H

#include "stack.h"
#include<string>
#include<vector>

// Insecure Hashing Algorithm (probably)
class IHA {
private:
    Stack s;
public:
    IHA();
    void hash(std::string);
    void permute_one(std::vector<std::string>);
    void permute_two(std::vector<std::string>);
};

#endif