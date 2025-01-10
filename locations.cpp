#include <iostream>
#include <vector>
#include <fstream>


using namespace std;


int main(){
// In tower

    int level_first[100][100];

    cout << sizeof(level_first) / 4 << endl;

    for(int i = 0;i < sizeof(level_first) / 4;++i){
        for(int j = 0; j < sizeof(level_first[i]) / 4;++j){
              level_first[i][j] = 3;
           
        }
    }

    ofstream outFile("1level.bin", ios::binary);
    
    outFile.write(reinterpret_cast<const char*>(level_first), sizeof(level_first));

    outFile.close();

    
    ifstream inFile("1level.bin", ios::binary);
    
    inFile.read(reinterpret_cast<char*>(level_first) , sizeof(level_first));

    inFile.close();


    for(int i = 0 ; i < 100 ; ++i){
        for(int j = 0 ; j < 100 ; ++j){
            cout << level_first[i][j];
        }
        cout << endl;
    }
    return 0;
}