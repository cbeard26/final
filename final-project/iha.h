#ifndef IHA_H
#define IHA_H

#include "stack.h"
#include <string>
#include <vector>

/**
 * @brief the IHA (Insecure Hashing Algorithm) object, contains information requires to hash text.
*/
class IHA {
private:
    std::string w1;  // initialized as a random binary number from 0-255
    std::string w2;  // initialized as a random binary number from 0-255
    std::string w3;  // initialized as a random binary number from 0-255
    std::string w4;  // initialized as a random binary number from 0-255
    std::vector<std::string> words; // stores the four words in one location for easier copying
    std::vector<std::string> bichars; // stores message as vector of binary integers as strings
public:
    IHA();
    std::vector<std::string> to_bichar_vec(std::string);
    std::string hash(std::string);
    int bin_to_dec(std::string);
    std::string dec_to_bin(int);
    void permute_one();
    void permute_two();
    void sub_one();
    void sub_two();
    void sub_three();
    void sub_four();
    void reset();
};

#endif