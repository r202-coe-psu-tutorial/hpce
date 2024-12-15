#include <iostream>

using namespace std;

auto fn(auto a, auto b){
    auto c = a+b;
    return c;
}

auto fn2(auto a, auto &b){
    a+=1;
    b+=1;
    return 0;
}


auto fn3(int a, int b=10){
    cout <<"int " <<a << " " << b << endl;
    return 0;
}


auto fn3(float a, float b=10, float c=10){
    cout << "float " <<a << " " << b << endl;
    return 0;
}


int main(){

    cout << 1 << " " << 2 << " " << fn(1,2) << endl;
    cout << 1 << " " << 2.2 << " " << fn(1.0,2.2) << endl;

    int x = 10;
    int y = 20;
    cout << x << " "<< y << endl;
    cout << fn2(x,y) << endl;
    cout << x << " "<< y << endl;

    cout << fn3(5) <<endl;
    cout << fn3(5.0, 10.0, 11.0) <<endl;
    return 0;
}
