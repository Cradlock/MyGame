#ifndef GROUP_H
#define GROUP_H

#include "../resourses.h"

class Group{
    string title;
    string description;
public:
    Group(string tit,string desc);
};

class Race{
    string title;
    string description;
public:
    Race(string tit,string desc);
};

extern unordered_map<string,Group> GLOBAL_Groups_list;

extern unordered_map<string,Race> GLOABL_Races_list;

#endif