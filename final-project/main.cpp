/**
 * This program takes a string as input and outputs a 4 byte hash message representing that string
 * 
 * @file main.cpp
 * @author Charlie Beard
 * @date 3 May, 2023
 */

#include <iostream>
#include "iha.h"

/**
 * @brief controls operation
*/
int main() {
    IHA iha;
    std::string s;
    while (s != "quit") {
        std::cout << "Message to Hash:\n";
        std::getline(std::cin, s);
        if (s != "quit") {
            std::cout << iha.hash(s) << std::endl;
        }
    }
}