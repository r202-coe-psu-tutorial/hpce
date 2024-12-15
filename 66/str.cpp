#include <string>
#include <cstring>

using namespace std;

int main (){
    char str1[] = "hello";
    // char* str2 = "world";
    char str3[20] = "PSU123456";

    printf(str1);
    printf("\n");
    printf(str3);
    str3[3] = '\0';
    printf("\n");
    printf(str3);
    str3[3] = 'x';
    printf("\n");
    printf(str3);
    
    return 0;
}
