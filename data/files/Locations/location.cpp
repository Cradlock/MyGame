#include "location.h"


string base = "files/Locations/mapsMatrix/";

namespace Maps_pathes{
    unordered_map<int,vector<string>> maps = {
        {1,{
            base + "level_zero.txt",
            base + "level_zero_objects.txt",
        }},
    };
}

vector<matrixMap> getLocation(int num){
    string pathTexture = Maps_pathes::maps[num][0];
    string pathObject = Maps_pathes::maps[num][1];

    matrixMap map;
    matrixMap mapObjects;
    string line;
    

    ifstream file(pathTexture);

    if (!file) {
        cerr << "Error! -> " << pathTexture << ' ' << pathObject << endl;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;

        int num;
        while (ss >> num) {
            row.push_back(num);
        }

        map.push_back(row);
    }
    file.close();
    line = "";

    ifstream fileObj(pathObject);
    
    while (getline(fileObj, line)) {
        stringstream ss(line);
        vector<int> row;

        int num;
        while (ss >> num) {
            row.push_back(num);
        }

        mapObjects.push_back(row);
    }
    fileObj.close();


    return vector<matrixMap>{ map,mapObjects };
};