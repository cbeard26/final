#ifndef IHA_H
#define IHA_H

#include "stack.h"
#include<string>
#include<vector>

// Insecure Hashing Algorithm (probably)
class IHA {
private:
    std::string w1; 
    std::string w2;
    std::string w3; 
    std::string w4; 
    std::vector<std::string> words;
public:
    IHA();
    std::vector<std::string> to_bichar_vec(std::string);
    std::string hash(std::string);
    int bin_to_dec(std::string);
    std::string dec_to_bin(int);
    void permute_one(std::vector<std::string>);
    void permute_two(std::vector<std::string>);
    void sub_one(std::vector<std::string>);
    void sub_two(std::vector<std::string>);
    void sub_three(std::vector<std::string>);
    void sub_four(std::vector<std::string>);
    void reset_words();
};

#endif