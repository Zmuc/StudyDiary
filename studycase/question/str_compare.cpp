#include <iostream>
using namespace std;

int main()
{
    /*
    */
    char str1[] = "abc";
    char str2[] = "abc";

    const char str3[] = "abc";
    const char str4[] = "abc";

    const char *str5 = "abc";
    const char *str6 = "abc";

    char *str7 = "abc";
    char *str8 = "abc";

    // == 比较的是地址
    cout << (str1 == str2) << endl; // 0
    cout << (str3 == str4) << endl; // 0
    cout << (str5 == str6) << endl; // 1
    cout << (str7 == str8) << endl; // 1

    return 0;
}