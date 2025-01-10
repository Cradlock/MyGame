#ifndef LAMBDADB_H
#define LAMBDADB_H





#include "constants.h"



class LambdaStorage{
private:
   static const unordered_map<int,function<void()>> functions;
public:
    static const std::unordered_map<int, function<void()>>& getLambdas() {
        return functions;
    }
};

const unordered_map<int, function<void()>> LambdaStorage::functions = {
    {0, 
     []() {
        std::cout << "Hello, world!" << std::endl;
     }
    }
    
};

#endif