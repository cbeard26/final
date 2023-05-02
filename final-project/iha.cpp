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
const int NUM_BIT_SIZE = 256;
const int NUM_BIT_SIZE_SQRT = 16;

IHA::IHA() {

    srand (time(NULL));

    w1 = dec_to_bin(rand() % 256);
    w2 = dec_to_bin(rand() % 256);
    w3 = dec_to_bin(rand() % 256);
    w4 = dec_to_bin(rand() % 256);
    std::string w1c = w1;
    std::string w2c = w2;
    std::string w3c = w3;
    std::string w4c = w4;
    words = {w1c, w2c, w3c, w4c};
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
    std::string left = dec_to_bin(bichars.size() % NUM_BIT_SIZE_SQRT);
    while (bichars.size() % NUM_BIT_SIZE_SQRT != 0) {
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
    std::string key = w1 + " " + w2 + " " + w3 + " " + w4;
    reset_words();
    return key;
}



void IHA::permute_one(std::vector<std::string> bichars) {
    if (bichars.size() % 4 == 0) {
        sub_one(bichars);
    } else if (bichars.size() % 4 == 1) {
        sub_two(bichars);
    } else if (bichars.size() % 4 == 2) {
        sub_three(bichars);
    } else {
        sub_four(bichars);
    }
}

//reverse
void IHA::sub_one(std::vector<std::string> bichars) {
    std::vector<std::string> bichars_copy = bichars;
    for (int i = 0; i < bichars_copy.size(); i++) {
        bichars[i] = bichars_copy[bichars_copy.size() - (i + 1)];
    }
    sub_four(bichars);
}

//equal caesar
void IHA::sub_two(std::vector<std::string> bichars) {
    for (int i = 0; i < bichars.size(); i++) {
        bichars[i] = dec_to_bin((bin_to_dec(bichars[i]) + (NUM_BIT_SIZE_SQRT)) % NUM_BIT_SIZE);
    }
    sub_four(bichars);
}

//unequal caesar + equal caesar
void IHA::sub_three(std::vector<std::string> bichars) {
    for (int i = 0; i < bichars.size(); i++) {
        bichars[i] = dec_to_bin((bin_to_dec(bichars[i]) + (bin_to_dec(bichars[i]) % NUM_BIT_SIZE_SQRT)) % NUM_BIT_SIZE);
    }
    for (int i = 0; i < bichars.size(); i++) {
        bichars[i] = dec_to_bin((bin_to_dec(bichars[i]) + (NUM_BIT_SIZE_SQRT)) % NUM_BIT_SIZE);
    }
    sub_four(bichars);
}

void IHA::sub_four(std::vector<std::string> bichars) {
    Stack s1;
    Stack s2;
    Stack s3;
    for (int i = 0; i < bichars.size(); i++) {
        if (bin_to_dec(bichars[i]) % (NUM_BIT_SIZE / NUM_BIT_SIZE_SQRT) > 10) {
            s1.push(bin_to_dec(bichars[i]));
        } else if (bin_to_dec(bichars[i]) % (NUM_BIT_SIZE / NUM_BIT_SIZE_SQRT) > 5) {
            s2.push(bin_to_dec(bichars[i]));
        } else {
            s3.push(bin_to_dec(bichars[i]));
        }
    }
    int c = 0;
    while (!s1.empty() && !s2.empty() && !s3.empty()) {
        bichars[c] = dec_to_bin((bin_to_dec(bichars[c]) + s1.pop() + s2.pop() + s3.pop()));
        c++;
    }
    for (int c; c < bichars.size(); c++) {
        bichars[c] = dec_to_bin((bin_to_dec(bichars[c]) % NUM_BIT_SIZE_SQRT) * NUM_BIT_SIZE_SQRT);
    }
}

void IHA::permute_two(std::vector<std::string> bichars) {
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
            w1 = dec_to_bin((bin_to_dec(w1) + n) % NUM_BIT_SIZE);
        } else if (n > floor(2 * PERM_1_MAX / 3)) {
            if ((bin_to_dec(w2) * 3 * n) % NUM_BIT_SIZE != 0) {
                w2 = dec_to_bin((bin_to_dec(w2) * 3 * n) % NUM_BIT_SIZE);
            }
        } else if (n > floor(PERM_1_MAX / 3)) {
            if (((NUM_BIT_SIZE - n) * bin_to_dec(w3)) % NUM_BIT_SIZE != 0) {
                w3 = dec_to_bin(((NUM_BIT_SIZE - n) * bin_to_dec(w3)) % NUM_BIT_SIZE);
            }
        } else {
                w4 = dec_to_bin((4 * bin_to_dec(w1)) + (3 * bin_to_dec(w2)) + (2 * bin_to_dec(w3)) + bin_to_dec(w4) % NUM_BIT_SIZE);
        }
    }
}

void IHA::reset_words() {
    w1 = words[0];
    w2 = words[1];
    w3 = words[2];
    w4 = words[3];
}

// Credit to this site for the simplified binary number retrieval: https://en.cppreference.com/w/cpp/utility/bitset