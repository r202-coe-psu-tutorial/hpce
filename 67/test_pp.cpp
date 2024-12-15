#include <iostream>

int main(){

    int a = 10;
    int b = a++;
    int c = a++ + 0;
    std::cout << "a=" << a << std::endl;
    std::cout << "b=" << b << std::endl;
    std::cout << "c=" << c << std::endl;
    return 0;
}
