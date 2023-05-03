#include "iha.h"
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int NUM_OF_PERMUTATIONS = 4;
const int PERM_1_MAX = 380;
const int NUM_BIT_SIZE = 256;
const int NUM_BIT_SIZE_SQRT = 16;

/**
 * @brief IHA object constructor, initializes class variables (words and vectoer of words)
*/
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

/**
 * @brief converts a number from binary (as string) to decimal (as integer)
 * 
 * @param bin a binary number stored as a string
 * @return the integer form of bin
*/
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

/**
 * @brief converts a number from decimal (as integer) to binary (as string).
 * uses the method to_string from the bitset library. 
 * Found here: https://en.cppreference.com/w/cpp/utility/bitset
 * 
 * @param n an integer 
 * @return the binary form of n, as a string
*/
std::string IHA::dec_to_bin(int n) {
    return std::bitset<8>(n).to_string();
}

/**
 * @brief takes a string and returns a vector containing binary representations of the ASCII values of each character
 * 
 * @param str a string
 * @return a list of the binary numbers stored as strings
*/
std::vector<std::string> IHA::to_bichar_vec(std::string str) {
    for (char ch : str) {
        bichars.push_back(dec_to_bin(int(ch)));
    }
    std::string left = dec_to_bin(bichars.size() % NUM_BIT_SIZE_SQRT);
    while (bichars.size() % NUM_BIT_SIZE_SQRT != 0) {
        bichars.push_back(left);
    }
    return bichars;
}

/**
 * @brief takes a string and hashes it into a unique (hopefully) binary message
 * 
 * @param inp the string to be hashed
 * @return a 32 bit (4 byte) binary message representing the hashed string
*/
std::string IHA::hash(std::string inp) {
    bichars = to_bichar_vec(inp);
    for (int i = 0; i < NUM_OF_PERMUTATIONS; i++) {
        permute_one();
        permute_two();
    }
    std::string key = w1 + " " + w2 + " " + w3 + " " + w4;
    reset();
    return key;
}

/**
 * @brief distributes tasks to the four primary sub permutor functions
*/
void IHA::permute_one() {
    if (bichars.size() % 4 == 0) {
        sub_one();
    } else if (bichars.size() % 4 == 1) {
        sub_two();
    } else if (bichars.size() % 4 == 2) {
        sub_three();
    } else {
        sub_four();
    }
}

/**
 * @brief permutes the bichars vector by reversing its order
 * directs to sub_four
*/
void IHA::sub_one() {
    std::vector<std::string> bichars_copy = bichars;
    for (int i = 0; i < bichars_copy.size(); i++) {
        bichars[i] = bichars_copy[bichars_copy.size() - (i + 1)];
    }
    sub_four();
}

/**
 * @brief permutes the bichars vector by appling a caesar cipher to it
 * directs to sub_four
*/
void IHA::sub_two() {
    for (int i = 0; i < bichars.size(); i++) {
        bichars[i] = dec_to_bin((bin_to_dec(bichars[i]) + (NUM_BIT_SIZE_SQRT)) % NUM_BIT_SIZE);
    }
    sub_four();
}

/**
 * @brief permutes the bichars vector by applying two caesar ciphers to it, 
 * one of flat value and one of variable value
 * directs to sub_four
*/
void IHA::sub_three() {
    for (int i = 0; i < bichars.size(); i++) {
        bichars[i] = dec_to_bin((bin_to_dec(bichars[i]) + (bin_to_dec(bichars[i]) % NUM_BIT_SIZE_SQRT)) % NUM_BIT_SIZE);
    }
    for (int i = 0; i < bichars.size(); i++) {
        bichars[i] = dec_to_bin((bin_to_dec(bichars[i]) + (NUM_BIT_SIZE_SQRT)) % NUM_BIT_SIZE);
    }
    sub_four();
}

/**
 * @brief shuffles the bichars in an unpredictable manner using several stacks
*/
void IHA::sub_four() {
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
        bichars[c] = dec_to_bin((bin_to_dec(bichars[c]) + s1.pop() + s2.pop() + s3.pop()) % NUM_BIT_SIZE);
        c++;
    }
    for (int c; c < bichars.size(); c++) {
        bichars[c] = dec_to_bin((bin_to_dec(bichars[c]) % NUM_BIT_SIZE_SQRT) * NUM_BIT_SIZE_SQRT);
    }
}

/**
 * @brief modifies the hash message words based on the contents of bichars
*/
void IHA::permute_two() {
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

/**
 * @brief resets the bichars list and the words to their original state
 * to allow the user to hash a new message in the same environments
*/
void IHA::reset() {
    w1 = words[0];
    w2 = words[1];
    w3 = words[2];
    w4 = words[3];
    bichars.clear();
}