#include<iostream>
#include "iha.h"

int main() {
    IHA iha;
    std::string s;
    std::cout << "Message to Hash:\n";
    std::cin >> s;
    std::cout << iha.hash(s) << std::endl;
}