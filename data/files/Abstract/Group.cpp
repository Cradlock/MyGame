#include "Group.h"

 
Group::Group(string tit,string desc) : title(tit) , description(desc){};

Race::Race(string tit,string desc) : title(tit) , description(desc){};



unordered_map<string,Group> GLOABL_Groups_list = {
    {}
};

unordered_map<string,Race> GLOABL_Races_list = {
    {"Human",Race{"Human","Default human"}}
};