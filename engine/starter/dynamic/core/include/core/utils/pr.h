#pragma once





#include <iostream>
template <typename T>
void print(const char* file, int line, T obj) {
    std::cout << "[" << file << ":" << line << "] " << obj << std::endl;
}



#define LOG_PRINT(obj) print(__FILE__, __LINE__, obj)


