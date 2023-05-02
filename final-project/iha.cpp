#include "iha.h"
#include<iostream>
#include<string>
#include<bitset>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cmath>

const int NUM_OF_PERMUTATIONS = 19;
const int PERM_1_MAX = 380;

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
    for (int i = 0; i < len; i++) {
        if (s[len - (i + 1)] == '1') {
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

void IHA::permute_one(std::vector<std::string> bichars) {
    Stack s;
    int curr = 0;
    for (int i = 0; i < bichars.size(); i++) {
        curr += bin_to_dec(bichars[i]);
        if (i % 4 == 0) {
            s.push(curr);
            curr = 0;
        }
    }
    while (!s.empty()) {
        int n = s.pop();
        if (n > PERM_1_MAX) {
            w1 = dec_to_bin((bin_to_dec(w1) + n) % 256);
        } else if (n > floor(2 * PERM_1_MAX / 3)) {
            w2 = dec_to_bin((bin_to_dec(w2) * 3 * n) % 256);
        } else if (n > floor(PERM_1_MAX / 3)) {
            w3 = dec_to_bin(((256 - n) * bin_to_dec(w3)) % 256);
        } else {
            w4 = dec_to_bin((4 * bin_to_dec(w1)) + (3 * bin_to_dec(w2)) + (2 * bin_to_dec(w3)) + bin_to_dec(w4) % 256);
        }
    }
}

void IHA::permute_two(std::vector<std::string>) {
    
}

// Credit to this site for the simplified binary number retrieval: https://en.cppreference.com/w/cpp/utility/bitset