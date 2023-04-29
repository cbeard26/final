#include "iha.h"
#include<iostream>
#include<string>
#include<bitset>
#include<vector>

const int NUM_OF_BASES = 4;
const int NUM_OF_PERMUTATIONS = 19;

IHA::IHA() {
    for (int i = 0; i < NUM_OF_BASES; i++) {
        s.push(10);
    }
}

void IHA::hash(std::string inp) {
    std::vector<std::string> bichars;
    for (char ch : inp) {
        bichars.push_back(std::bitset<8>(int(ch)).to_string());
    }
    std::string left = std::bitset<8>(bichars.size() % 16).to_string();
    while (bichars.size() % 16 != 0) {
        bichars.push_back(left);
    }

    for (int i = 0; i < NUM_OF_PERMUTATIONS; i++) {
        permute_one(bichars);
        permute_two(bichars);
    }
}

void IHA::permute_one(std::vector<std::string>) {

}

void IHA::permute_two(std::vector<std::string>) {

}

// Credit to this site for the simplified binary number retrieval https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting