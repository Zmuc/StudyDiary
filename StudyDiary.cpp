/* C++ 特性 */
  
// C++ 11：Range-based for loops
vector<int> vec;
for (int i : vec) { }
//循环执行容器vec中的所有数据


/* STL容器 */

// unordered_map：唯一键的键/值对元素hash表，无序
template < class Key,
           class T,
           class Hash = hash<Key>,
           class Pred = equal_to<Key>,
           class Alloc = allocator< pair<const Key,T> > > class unordered_map;
//Key：键
//T：值
//Hash，Pred，Alloc：一般不用


/* 数据类型 */

// pair：将2个数据组合成1组数据
template < class T1,
           class T2 > struct pair；
//T1，T2：int，string，vector<int>等数据类型


/* 算法 */

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
