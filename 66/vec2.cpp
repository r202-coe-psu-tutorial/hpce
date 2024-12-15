#include <iostream>
#include <vector>

using namespace std;

int main(){
    
    vector<int> arr2;
    for(auto i=0; i<10; ++i)
        arr2.push_back(i);

    for(auto &a: arr2){
        cout << a << endl;
        a+=1;
    }

    cout << "-----------------" <<endl;

    for(auto &a: arr2){
        cout << a << endl;
    }

    return 0;
}
