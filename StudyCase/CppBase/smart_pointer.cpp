#include <iostream>
#include <memory>

using namespace std;

int main()
{
    /* auto_ptr */
    auto_ptr<string> a_p1 (new string("auto_ptr")); 
    auto_ptr<string> a_p2; 
    a_p2 = a_p1;           // 不会报错，但a_p2剥夺了a_p1的所有权，此时调用a_p1会导致内存崩溃

    /* unique_ptr */
    unique_ptr<string> u_p1(new string("unique_ptr1")); 
    unique_ptr<string> u_p2; 
    //u_p2 = u_p1;                                          会报错，unique_ptr不允许此操作
    unique_ptr<string> u_p3; 
    u_p3 = unique_ptr<string>(new string("unique_ptr2"));  // 不会报错，该构造函数创建的临时对象在其所有权让给u_p3后就被销毁

    /* shared_ptr */
	shared_ptr<string> s_p1(new string("shared_ptr1"));
	shared_ptr<string> s_p2;
	s_p2 = s_p1;                            // s_p1，s_p2共享

	cout << s_p1.use_count() << endl;	    // 2，s_p1，s_p2共享shared_ptr1
	cout << s_p2.use_count() << endl;	    // 2，s_p1，s_p2共享shared_ptr1
	cout << s_p1.unique() << endl;	        // 0，非独占，所以是false

	shared_ptr<string> s_p3(new string("shared_ptr2"));

	cout << s_p1.get() << endl;	            // A地址
	cout << s_p3.get() << endl;	            // B地址
	swap(s_p1, s_p3);	                    // 交换所拥有的对象
	cout << s_p1.get() << endl;	            // B地址
	cout << s_p3.get() << endl;	            // A地址

	cout << s_p1.use_count() << endl;	    // 1，s_p1独占shared_ptr2
	cout << s_p2.use_count() << endl;	    // 2，s_p2，s_p3共享shared_ptr1
	s_p2 = s_p1;                            // s_p2 -> s_p1所独占shared_ptr2
	cout << s_p1.use_count() << endl;	    // 2，s_p1，s_p2共享shared_ptr2
	cout << s_p2.use_count() << endl;	    // 2，s_p1，s_p2共享shared_ptr2
	s_p1.reset();	                        // 放弃s_p1的拥有权，shared_ptr2引用计数的减少
	cout << s_p1.use_count()<<endl;	        // 0，s_p1未拥有
	cout << s_p2.use_count()<<endl;	        // 1，s_p2独占shared_ptr2
}
