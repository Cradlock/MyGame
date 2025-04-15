#ifndef ESSENCEDB_H
#define ESSENCEDB_H


#include "links.h"

extern unordered_map<int,function<void(Essence& self)>> EssencesLambdaDB;

extern void init_essence_lambdas();

#endif