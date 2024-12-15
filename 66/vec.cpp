#include <iostream>
#include <vector>

using namespace std;

int main(){
    
    int arr1 [10] = {0};
    vector<float> arr2;
    for(auto i=0; i<10; ++i)
        arr2.push_back(i*.1);

    for(auto i=0; i<10; ++i)
        arr2.push_back(i);

    for(auto it=arr2.begin(); it != arr2.end(); it++)
        cout << *it << endl;
    cout << "-----------------" <<endl;
    for(auto a: arr2)
        cout << a << endl;


    return 0;
}
