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