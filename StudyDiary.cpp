/* C++ 特性 */
// C++ 11：Range-based for loops
vector<int> vec;
for (int i : vec) { }
//循环执行容器vec中的所有数据


/* 排序 */

// sort：排序
void sort (first_pointer, first_pointer+n, cmp);
//first_pointer：即数组，链表，队列，容器等首地址，长度为n；
//cmp：即排序算法，可自定义，less<data-type>()升序，greater<data-type>()降序，默认升序。

/* 内存管理 */

// memset：初始化内存
void *memset(void *buffer, int n, int count)；
//buffer：指针或者数组，void是要初始化的内存的首地址；
//n：初始化后的int数据；
//count：buffer的初始化长度
