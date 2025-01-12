#ifndef LOCATION_H
#define LOCATION_H


#include <vector>
#include "../resourses.h"
#include "../Object/ObjectBaseClass.h"


using namespace std;

extern string base;

namespace Maps_pathes{
   extern unordered_map<int,vector<string>> maps;
}


vector<matrixMap> getLocation(int n);




#endif 