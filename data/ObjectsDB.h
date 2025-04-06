#ifndef OBJECTSDB_H
#define OBJECTSDB_H

#include <files/Object/ObjectBaseClass.h>
#include <files/Essence/EssenceBaseClass.h>

extern unordered_map<int,function<void(Object& self,Essence& esse)>> ObjectsDB;



#endif