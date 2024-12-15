#include <iostream>
#include <cstdio>
using namespace std;


int main(){
    int a;
    float b;
    int *ptr = new int;
    int *pptr;
    cout << "a: "<< &a << " : "<< a<< endl
        << "b: "<< &b << " : " << b <<endl
        << "ptr addr : "<< ptr << endl
        << "ptr: "<< &ptr << endl
        << "pptr: "<< &pptr << endl;
    {
        {
            { 
                int d=10;
            }
        }
    }

    return 0;
}
