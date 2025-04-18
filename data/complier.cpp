#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;
int main(){
    freopen("code.txt","r",stdin);
    string complier_command;
    getline(cin,complier_command,'\n');
   
    system(complier_command.c_str());
    return 0; 
}