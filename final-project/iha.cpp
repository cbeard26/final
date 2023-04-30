#include "iha.h"
#include<iostream>
#include<string>
#include<bitset>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>

const int NUM_OF_BASES = 4;
const int NUM_OF_PERMUTATIONS = 19;

IHA::IHA() {

    srand (time(NULL));

    w1 = dec_to_bin(rand() % 256);
    w2 = dec_to_bin(rand() % 256);
    w3 = dec_to_bin(rand() % 256);
    w4 = dec_to_bin(rand() % 256);

    std::cout << "Keyswords: " << w1 << " " << w2 << " " << w3 << " " << w4 << std::endl;
}

int IHA::bin_to_dec(std::string bin) {
    std::vector<char> s;
    for (char c : bin) {
        s.push_back(c);
    }
    int total = 0;
    int len = s.size();
    for (int i = 1; i <= len; i++) {
        if (s[len - i] == '1') {
            total += pow(2, i);
        }
    }
    return total;
}

std::string IHA::dec_to_bin(int n) {
    return std::bitset<8>(n).to_string();
}

std::vector<std::string> IHA::to_bichar_vec(std::string str) {
    std::vector<std::string> bichars;
    for (char ch : str) {
        bichars.push_back(dec_to_bin(int(ch)));
    }
    std::string left = dec_to_bin(bichars.size() % 16);
    while (bichars.size() % 16 != 0) {
        bichars.push_back(left);
        std::cout << left << " as decimal: " << bin_to_dec(left) << std::endl;;
    }
    return bichars;
}

std::string IHA::hash(std::string inp) {
    std::vector<std::string> bichars = to_bichar_vec(inp);

    for (int i = 0; i < NUM_OF_PERMUTATIONS; i++) {
        permute_one(bichars);
        permute_two(bichars);
    }
    return w1 + w2 + w3 + w4;
}

void IHA::permute_one(std::vector<std::string>) {
    std::cout << "permute1" << std::endl; 
}

void IHA::permute_two(std::vector<std::string>) {
    std::cout << "permute2" << std::endl;
}

// Credit to this site for the simplified binary number retrieval https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting