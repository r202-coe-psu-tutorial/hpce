#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main(){
    
    string str1 = "Hello";
    string str2 = "world";

    string str3 = str1 + " " + str2;

    cout << str1 << endl
        << str2 << endl
        << str3 << endl;
    cout << str1.c_str() <<endl;

    char *pstr = new char[str1.length() + 1];

    strcpy(pstr, str1.c_str());
    cout << pstr << endl;
    pstr[2] = '\0';
    cout << pstr << endl;

    return 0;
}
