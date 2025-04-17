#ifndef OBJECTSDB_H
#define OBJECTSDB_H


#include "links.h"

extern unordered_map<int,function<void(Object& self,Essence& esse)>> ObjectsDB;


extern void init_objects_lambdas();

#endif