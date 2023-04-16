#include "../include/other1.h"
#include <iostream>
#include <fstream>
#include <string>

void TestOther1(){
    std::cout << "Other1\n";
}

void ReadFromTestFile(){
    std::ifstream file("assets/asi.txt");
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line))
        {
            std::cout << line << '\n';
        }
    }
}