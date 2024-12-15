#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> v={0,0,0,0};
    
    for(auto it = v.begin(); it != v.end(); it++){
        cout << *it << endl; 
    }
    for(auto &i:v){
        i = 10;
    }

    for(auto i:v){
        cout<< i << endl;
    }



}
