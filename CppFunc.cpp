/* ——————————————————————————————————————————————————
 * STL容器 */

/* unordered_map：唯一键的键/值对元素hash表，无序 */
template < class Key,
            class T,
            class Hash = hash<Key>,
            class Pred = equal_to<Key>,
            class Alloc = allocator< pair<const Key,T> > > class unordered_map;
// Key：键
// T：值
// Hash，Pred，Alloc：一般不用，可由map替代


/* ——————————————————————————————————————————————————
 * 算法 */

/* sort：排序 */
void sort (first_pointer, first_pointer+n, cmp);
// first_pointer：即数组，链表，队列，容器等首地址，长度为n
// cmp：即排序算法，可自定义，less<data-type>()升序，greater<data-type>()降序，默认升序

/* find：查找 */
template<class InputIterator, class T>；
InputIterator find (InputIterator first, InputIterator last, const T& val)；
// InputIterator：输入迭代器
// first，last：从first找到last，即[first, last)
// val：要查找的目标元素
// 返回值：返回一个输入迭代器，函数查找成功时，指向第一个目标元素；查找失败时，指向和last相同


/* ——————————————————————————————————————————————————
 * 数据类型 */

/* pair：将2个数据组合成1组数据 */
template < class T1,
            class T2 > struct pair；
// T1，T2：int，string，vector<int>等数据类型


/* ——————————————————————————————————————————————————
 * #include <string.h> */

/* memchr：匹配内存区域中的字节 */
void *memchr(const void *str, int c, size_t n);
// str：指向要执行搜索的内存块
// c：以int形式传递的值，但在每次字节搜索时是使用该值的无符号字符形式
// n：要被分析的字节数
// 返回值：指向匹配字节的指针，如果在给定的内存区域未出现字符，则返回 NULL

/* memcmp：比较两个存储区的前n个字节 */
int memcmp(const void *str1, const void *str2, size_t n);
// str1：指向内存块1的指针
// str2：指向内存块1的指针
// n：要被比较的字节数
// 返回值：值<0，则str1小于str2；值>0，则str1大于str2；值=0，则str1等于str2

/* memcpy：存储区复制 */
void *memcpy(void *dest, const void *src, size_t n);
// dest：指向用于存储复制内容的目标数组，类型强制转换为 void* 指针
// src：指向要复制的数据源，类型强制转换为 void* 指针
// n：要被复制的字节数
// 返回值：指向目标存储区str1的指针

/* memmove：存储区复制（重叠内存块处理上比memcpy安全） */
void *memmove(void *dest, const void *src, size_t n);
// dest：指向用于存储复制内容的目标数组，类型强制转换为 void* 指针
// src：指向要复制的数据源，类型强制转换为 void* 指针
// n：要被复制的字节数
// 返回值：指向目标存储区str1的指针

/* memset：初始化内存 */
void *memset(void *buffer, int n, int count)；
// buffer：指针或者数组，是要初始化的内存的首地址；
// n：初始化后的int数据；
// count：buffer的初始化长度

/* strcat, strncat：字符串连接 */
char *strcat(char *dest, char *src);
char *strncat(char *dest, char *src, size_t n);
// dest：指向目标数组，该数组包含了字符串，且足够容纳追加后的字符串，包括额外的空字符
// src：要追加的字符串（覆盖dest结尾处的'\0'）
// n：要复制的字符数
// 返回值：指向最终的目标字符串 dest 的指针

/* strcpy, strncpy：字符串复制 */
char *strcpy(char *dest, char *src);
char *strncpy(char *dest, char *src, size_t n);
// dest：指向用于存储复制内容的目标数组
// src：要复制的字符串
// n：要追加的最大字符数
// 返回值：最终复制的字符串


