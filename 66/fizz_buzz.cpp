#include <cstdio>
#include <iostream>

using namespace std;

int main(){
    int num;

    cout << "Enter Number: ";
    cin >> num;

    if(num % 3 == 0 && num % 5 == 0){
        cout << "FizzBuzz" << endl;
    }
    else if(num % 3 == 0){
        cout << "Fizz" << endl;
    }
    else if(num % 5 == 0){
        cout << "Buzz" << endl;
    }

    return 0;
}
