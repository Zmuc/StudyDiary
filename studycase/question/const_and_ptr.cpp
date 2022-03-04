#include <iostream>
using namespace std;

int main()
{
    /*
        const与指针
    */
    int x = 0;
    int y = 100;

    // 常量指针/常指针
    const int *p1 = &x;
    x = 1;       // 指向对象的值
    //*p1 = 4;   // 指向地址， ERROR
    p1 = &y;     // 指向其他对象

    // 指针常量
    int*  const p2 = &x;
    x = 2;
    *p2 = 8;
    //p2 = &y;    ERROR

    // 指向常量的常量指针
    const int* const p3 = &x;
    x = 3;
    //*p3 = 16;
    //p3 = &y;    ERROR

    return 0;
}