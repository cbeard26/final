#include<iostream>
#include "iha.h"

int main() {
    IHA iha;
    std::string s = "hello  ,. z123456";
    iha.hash(s);
    std::cout << std::endl;
}