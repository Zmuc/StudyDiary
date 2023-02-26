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


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * stdio.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

size_t   // 无符号整数类型（unsigned int）
FILE     // 存储文件流信息的类型
fpos_t   // 存储文件位置的类型

NULL                         // 空指针常量的值
EOF                          // 已达文末的负整数
stderr                       // 指向FILE类型的指针，标准错误流
stdin                        // 指向FILE类型的指针，标准输入流
stdout                       // 指向FILE类型的指针，标准输出流
SEEK_CUR|SEEK_END|SEEK_SET   // 见fseek()函数，定位不同的文件位置
_IOFBF|_IOLBF|_IONBF         // 见setvbuf()函数
BUFSIZ                       // 见setbuf()函数，缓冲区大小
FOPEN_MAX                    // 系统可以同时打开的文件数量
FILENAME_MAX                 // 字符数组可以存储的文件名最大长度
L_tmpnam                     // 字符数组可以存储的临时文件名（由tmpnam()函数创建）最大长度。
TMP_MAX                      // 由tmpnam()函数可生成的独特文件名最大数量

// ---------------------- 文件基本操作 ----------------------

/* fopen：打开文件 */
FILE *fopen(const char *filename, const char *mode);
// filename：文件路径（绝对路径，相对路径）
// mode：打开模式（t/b只能在r/w/a后）
//     - "r"：读
//     - "w"：写（文件存在则删除重建，不存在则新建）
//     - "a"：追加（文件存在则追加，不存在则新建）
//     - "r+"：读写
//     - "w+"：w和r+叠加（文件存在则删除重建，不存在则新建）
//     - "a+"：a和r+叠加（文件存在则追加，不存在则新建）
//     - "t"：文本文件（默认）
//     - "b"：二进制文件
// 返回值：文件流（失败：NULL）

/* freopen：以指定流stream重新打开文件（旧文件关闭） */
FILE *freopen(const char *filename, const char *mode, FILE *stream);
// filename：文件路径
// mode：打开模式
// stream：流（该文件流打开的旧文件关闭）
// 返回值：文件流（失败：NULL）

/* fclose：关闭文件并刷新缓冲区 */
int fclose(FILE *stream);
// stream：文件流
// 返回值：0（失败：EOF）

/* remove：删除文件 */
int remove(const char *filename);
// filename：文件路径
// 返回值：0（失败：-1）

/* rename：重命名/移动文件 */
int rename(const char *old_filename, const char *new_filename);
// old_filename：待重命名/移动文件
// new_filename：重命名/移动后文件
// 返回值：0（失败：-1）

/* tmpfile：打开临时文件（wb+模式），流关闭/程序终止时自动删除 */
FILE *tmpfile(void);
// 返回值：文件流（失败：NULL）

/* tmpnam：生成并返回临时文件名（之前不存在） */
char *tmpnam(char *str);
// str：临时文件名（NULL：指向内部缓冲区，且不生成临时文件名）
// 返回值：str（包含NULL）

// ---------------------- 文件位置 ----------------------

/* fgetpos：获取指定流stream的当前文件位置，并写入pos */
int fgetpos(FILE *stream, fpos_t *pos);
// stream：流
// pos：位置信息
// 返回值：非0（失败：0）

/* fsetpos：设置指定流stream的文件位置 */
int fsetpos(FILE *stream, const fpos_t *pos);
// stream：流
// pos：位置信息（通过fgetpos获取）
// 返回值：0（失败：非0）

/* ftell：返回指定流stream的当前文件位置 */
long int ftell(FILE *stream);
// stream：流
// 返回值：文件位置标识符（失败：-1L）

/* rewind：重置指定流stream的文件位置 */
void rewind(FILE *stream);
// stream：流

/* fseek：设置文件位置偏移 */
int fseek(FILE *stream, long int offset, int whence);
// stream：文件流
// offset：相对whence的偏移量（单位：字节）
// whence：
//     - SEEK_SET：文件开头
//     - SEEK_CUR：文件指针的当前位置
//     - SEEK_END：文件末尾
// 返回值：0（失败：非0）

// ---------------------- 标识符 ----------------------

/* feof：指定流stream的文件结束标识符 */
int feof(FILE *stream);
// stream：流
// 返回值：非0（失败：0）

/* ferror：指定流stream的错误标识符 */
int ferror(FILE *stream);
// stream：流
// 返回值：非0（失败：0）

/* clearerr：清除指定流的文件结束和错误标识符 */
void clearerr(FILE *stream);
// stream：流

// ---------------------- 缓冲 ----------------------

/* setbuf：设置指定流stream的缓冲 */
void setbuf(FILE *stream, char *buffer);
// stream：流
// buffer：缓冲（大小 >= BUFSIZ/宏常量）

/* setbuf：设置指定流stream的缓冲（详细） */
int setvbuf(FILE *stream, char *buffer, int mode, size_t size);
// stream：流
// buffer：缓冲
// mode：缓冲模式
//     - _IOFBF：全缓冲，缓冲满时写入，缓冲空时填充
//     - _IOLBF：行缓冲，缓冲满时/换行符时写入，缓冲空时/换行符时填充
//     - _IONBF：无缓冲，I/O操作即时写入，忽略buffer，size
// size：缓冲大小（字节）
// 返回值：0（失败：非0）

/* fflush：刷新输出缓冲区 */
int fflush(FILE *stream);
// stream：文件流
// 返回值：0（失败：EOF，并设置错误标识符feof）

// ---------------------- 格式化I/O ----------------------

/* fprintf：发送格式化输出到流stream */
int fprintf(FILE *stream, const char *format, ...);
// stream：流
// format：格式化：%[flags][width][.precision][length]specifier
//     - specifier：说明符
//         - c：字符
//         - s：字符串
//         - d/i：有符号十进制数
//         - o：有符号八进制数
//         - u：无符号十进制数
//         - x：无符号十六进制数
//         - X：无符号十六进制数（大写字母）
//         - f：浮点数
//         - e/E：e/E的科学计数法（指数，尾数）
//         - g/G：自动选择合适的e/E或f表示法
//         - p：指针地址
//     - flags：标识
//         - -：左对齐，默认右对齐（width）
//         - +：正数时显示+，默认不显示
//         - (space)：如果未写入任何符号，则保留个空格
//         - #：扩展
//             -  o/x/X：非零值前显示0/0x/0X
//             - e/E/f：强制包含一个小数点
//             - g/G：强制包含一个小数点，但尾部的0不清除
//         - 0：填充置0，默认空格（width）
//     - width：宽度
//         - (number)：要输出字符的最小数目（超过不截断，不足时右对齐，空格填充）
//         - *：format未指定，但作为附加整数值参数，放置于被格式化的参数前
//     - precision：精度
//         - .number：未指定为1，指定无显式值为0
//             -  d/i/o/u/x/X：数字的最小位数（0则不写入任何字符，超过不截断，不足时填充前置0）
//             -  f/e/E：小数点后的小数位数
//             -  g/G：最大有效位数
//             -  c：无影响
//             -  s：最大字符数，默认全部输出
//         - *：format未指定，但作为附加整数值参数，放置于被格式化的参数前
//     - length：长度
//         - h：短整型或无符号短整型/short int，仅适用d/i、o、u、x、X（整数说明符）
//         - l：长整型或无符号长整型/long int，仅使用d/i、o、u、x、X、c、s（整数说明符，字符说明符）
//         - L：长双精度型/long double，仅使用f、e、E、g、G（浮点数说明符）
// 返回值：字符总数（失败：<0）

/* printf：发送格式化输出到标准输出stdout */
int printf(const char *format, ...);
// format：格式化
// 返回值：字符总数（失败：<0）

/* sprintf：发送格式化输出到字符串 */
int sprintf(char *str, const char *format, ...);
// str：字符串
// format：格式化
// 返回值：不包括末尾追加的字符总数（失败：<0）

/* vfprintf：使用参数列表发送格式化输出到流stream */
int vfprintf(FILE *stream, const char *format, va_list arg);
// stream：流
// format：格式化
// arg：可变参数列表（由<stdarg>中va_start宏初始化）
// 返回值：不包括末尾追加的字符总数（失败：<0）

/* vprintf：使用参数列表发送格式化输出到标准输出stdout */
int vprintf(const char *format, va_list arg);
// format：格式化
// arg：可变参数列表
// 返回值：不包括末尾追加的字符总数（失败：<0）

/* vsprintf：使用参数列表发送格式化输出到字符串 */
int vsprintf(char *str, const char *format, va_list arg);
// str：字符串
// format：格式化
// arg：可变参数列表
// 返回值：不包括末尾追加的字符总数（失败：<0）

/* snprintf：将可变参数格式化为字符串并拷贝写入 */
int snprintf(char *str, size_t size, const char *format, ...);
// str：待拷贝的字符串
// size：拷贝大小（字节）
// format：格式化
// ...：可变参数
// 返回值：写入的字符串大小（格式化大小 >= size则截断+\0；格式化大小 < size则全拷贝+\0）

/* fscanf：从流stream读取格式化输入 */
int fscanf(FILE *stream, const char *format, ...);
// stream：流
// format：格式化
// 返回值：成功匹配格式化和赋值的个数（失败/到达文末：EOF）

/* scanf：从标准输入stdin读取格式化输入 */
int scanf(const char *format, ...);
// format：格式化
// 返回值：成功匹配格式化和赋值的个数（失败/到达文末：EOF）

/* sscanf：从字符串读取格式化输入 */
int sscanf(const char *str, const char *format, ...);
// str：字符串
// format：格式化
// 返回值：成功匹配格式化和赋值的个数（失败/到达文末：EOF）

// ---------------------- I/O ----------------------

/* fread：读取指定流stream的数据，并写入 */
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
// ptr：指针，指向最小尺寸size*nmemb字节的内存块
// size：每个元素的大小（字节）
// nmemb：元素的个数
// stream：流
// 返回值：实际读取的元素总个数（不一致原因：错误/已读到文末）

/* fwrite：将流数据写入到指定流stream */
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
// ptr：指针，指向最小尺寸size*nmemb字节的内存块
// size：每个元素的大小（字节）
// nmemb：元素的个数
// stream：流
// 返回值：实际写入的元素总个数（不一致原因：错误/已写完）

/* getc：从指定流stream获取下一个字符，并移动文件位置 */
int getc(FILE *stream);
// stream：流
// 返回值：读取的字符/无符号char->int（失败/到达文末：EOF）

/* fgetc：从指定流stream获取下一个字符，并移动文件位置 */
int fgetc(FILE *stream);
// stream：流
// 返回值：读取的字符/无符号char->int（失败/到达文末：EOF）

/* fgets：从指定流stream获取一行（n/换行符/文末），并移动文件位置 */
char *fgets(char *str, int n, FILE *stream);
// str：字符串
// n：从文件流中读取n个字符
// stream：流
// 返回值：str（失败/到达文末/读取为空：NULL）

/* getchar：从标准输入stdin获取下一个字符，并移动文件位置 */
int getchar(void);
// 返回值：读取的字符/无符号char->int（失败/到达文末：EOF）

/* gets：从标准输入stdin获取一行（换行符/文末），写入字符串，并移动文件位置 */
char *gets(char *str);
// str：字符串
// 返回值：str（失败/到达文末/读取为空：NULL）

/* putc：把指定字符写入指定流stream，并移动文件位置 */
int putc(int char, FILE *stream);
// char：无符号字符（int型）
// stream：流
// 返回值：写入的字符/无符号char->int（失败：EOF）

/* fputc：把指定字符写入指定流stream，并移动文件位置 */
int fputc(int char, FILE *stream);
// char：无符号字符（int型）
// stream：流
// 返回值：写入的字符/无符号char->int（失败：EOF）

/* fputs：把指定字符串（不包括末空字符）写入指定流stream，并移动文件位置 */
int fputs(const char *str, FILE *stream);
// str：字符串
// stream：流
// 返回值：>=0（失败：EOF）

/* putchar：把指定字符写入标准输出stdout，并移动文件位置 */
int putchar(int char);
// char：无符号字符（int型）
// 返回值：写入的字符/无符号char->int（失败：EOF）

/* puts：把指定字符串（不包括末空字符，包括换行符）写入标准输出stdout，并移动文件位置 */
int puts(const char *str);
// str：字符串
// 返回值：包括\0的字符串长度（失败：EOF）

/* perror：将描述性错误消息输出到标准错误stderr */
void perror(const char *str);
// str：字符串（perror("Error: ") -> Error: : xxx/来自stderr）

/* ungetc：把指定字符写入指定流stream，且该字符是下一个被读取到的 */
int ungetc(int char, FILE *stream);
// char：无符号字符（int型）
// stream：流
// 返回值：写入的字符/无符号char->int（失败：EOF）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * stdlib.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

size_t   // 无符号整数类型（unsigned int）
wchar_t  // 宽字符常量大小的整数类型
div_t    // div()函数返回类型
ldiv_t   // ldiv()函数返回类型

NULL            // 空指针常量的值
EXIT_FAILURE    // exit()函数失败时返回值
EXIT_SUCCESS    // exit()函数成功时返回值
RAND_MAX        // rand()函数返回的最大值
MB_CUR_MAX      // 多字节字符集中的最大字符数

// ---------------------- 类型转换 ----------------------

/* atof：字符串 -> double */
double atof(const char *str);
// str：待转换的字符串
// 返回值：转换后的double浮点数（失败：0.0）

/* atoi：字符串 -> int */
int atoi(const char *str);
// str：待转换的字符串
// 返回值：转换后的int整数（失败：0）

/* atol：字符串 -> long int */
long int atol(const char *str);
// str：待转换的字符串
// 返回值：转换后的long int整数（失败：0）

/* strtod：字符串 -> double */
double strtod(const char *str, char **endptr);
// str：待转换的字符串
// endptr：str中数值后的下一个字符
// 返回值：转换后的double浮点数（失败：0.0）

/* strtol：字符串 -> long int */
long int strtol(const char *str, char **endptr, int base);
// str：待转换的字符串
// endptr：str中数值后的下一个字符
// base：转换基数，2 <= base <= 36/base = 0
// 返回值：转换后的long int整数（失败：0）

/* strtoul：字符串 -> unsigned long int */
unsigned long int strtoul(const char *str, char **endptr, int base);
// str：待转换的字符串
// endptr：str中数值后的下一个字符
// base：转换基数，2 <= base <= 36/base = 0
// 返回值：转换后的unsigned long int整数（失败：0）

// ---------------------- 内存空间 ----------------------

/* calloc：分配内存空间 */
void *calloc(size_t nitems, size_t size);
// nitems：分配的元素数目
// size：元素大小
// 返回值：指向已分配内存的指针（失败：NULL）
// int *a = (int*)calloc((int)n, sizeof(int));

/* malloc：分配内存空间 */
void *malloc(size_t size);
// size：内存块大小（字节）
// 返回值：指向已分配内存的指针（失败：NULL）

/* realloc：调整内存空间（calloc/malloc）大小 */
void *realloc(void *ptr, size_t size);
// ptr：calloc|malloc
// size：内存块新的大小（字节），若大小为0且ptr切实指向某个内存块，则释放
// 返回值：指向已调整内存的指针（失败/释放：NULL）

/* free：释放内存空间 */
void free(void *ptr);
// ptr：calloc|malloc|realloc

// ---------------------- 程序状态----------------------

/* exit：正常终止程序 */
void exit(int status);
// status：返回给父进程的状态值

/* abort：终止异常程序 */
void abort(void);
// 无参数无返回值：中止程序执行，从调用处直接跳出

/* atexit：程序正常终止时，调用指定的函数 */
int atexit(void (*func)(void));
// func：程序终止时被调用的函数
// 返回值：0（失败：非0）

// ---------------------- 环境切换 ----------------------

/* getenv：获取环境变量 */
char *getenv(const char *name);
// name：环境变量
// 返回值：环境变量值（失败：NULL）

/* system：在主机环境执行命令 */
int system(const char *string);
// string：执行命令
// 返回值：命令状态（失败：-1）

// ---------------------- 算术 ----------------------

/* bsearch：二分查找 */
void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));
// key：指向要查找的元素
// base：指向查找数组的第一个元素（类型转换为void*）
// nitems：base指向数组的元素个数
// size：base指向数组的元素大小（字节）
// compar：比较两个元素的函数
// 返回值：匹配元素的指针（失败：NULL）

/* qsort：数组排序 */
void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));
// base：指向排序数组的第一个元素（类型转换为void*）
// nitems：base指向数组的元素个数
// size：base指向数组的元素大小（字节）
// compar：比较两个元素的函数

/* qsort：绝对值 */
int abs(int x);
// x：取绝对值的数（int）
// 返回值：|x|（绝对值）

/* labs：绝对值 */
long int labs(long int x);
// x：取绝对值的数（long int）
// 返回值：|x|（绝对值）

/* qsort：分子 ÷ 分母 */
div_t div(int numer, int denom);
// numer：分子
// denom：分母
// 返回值：div_t结构（int quot; int rem;）

/* ldiv：分子 ÷ 分母 */
ldiv_t ldiv(long int numer, long int denom);
// numer：分子
// denom：分母
// 返回值：ldiv_t结构（long quot; long rem;）

/* rand：0到RAND_MAX间的伪随机数 */
int rand(void);
// 返回值：[0, RAND_MAX]

/* srand：随机数发生器 */
void srand(unsigned int seed);
// seed：伪随机数生成算法，即设定rand()返回值[seed, RAND_MAX]

// ---------------------- 多字节字符 && 宽字符 ----------------------

/* mblen：返回多字节字符的长度 */
int mblen(const char *str, size_t n);
// str：指向多字节字符（char *）的第一个字节的指针
// n：被检查的最大字节数
// 返回值：检查的字节数（失败：空宽字符=0，无效多字节字符=-1）

/* mbtowc：将多字节字符转换为宽字符 */
int mbtowc(whcar_t *pwc, const char *str, size_t n);
// pwc：指向宽字符的指针
// str：指向多字节字符的第一个字节的指针
// n：被转换的最大字节数
// 返回值：转换的字节数（失败：-1/NULL：0）

/* wctomb：将宽字符转换为多字节字符 */
int wctomb(char *str, wchar_t wchar);
// str：指向多字节字符（足够存储）
// wchar：宽字符
// 返回值：写入str中的字节数（失败：-1/NULL：0）

/* mbstowcs：将多字节字符串转换为宽字符串 */
size_t mbstowcs(wchar_t *pwcs, const char *str, size_t n);
// pwcs：宽字符串（足以存储一个最大字符长度的宽字符数组）
// str：被转换的多字节字符字符串
// n：被转换的最大字符数
// 返回值：转换的字符数（失败：-1）

/* wcstombs：将宽字符串转换为多字节字符串 */
size_t wcstombs(char *str, const wchar_t *pwcs, size_t n);
// str：多字节字符串（大小>=n）
// pwcs：被转换的宽字符串
// n：被转换的最大字节数
// 返回值：转换和写入的字节数（失败：-1）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * string.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

size_t   // 无符号整数类型（unsigned int）

NULL     // 空指针常量的值

// ---------------------- 存储区 ----------------------

/* memchr：存储区检索：检索存储区前n个字节中首次出现字符c的位置 */
void *memchr(const void *mem, int c, size_t n);
// mem：存储区/内存块
// c：检索字符，以int形式传递的值（无符号字符）
// n：检索的字节数
// 返回值：指向匹配字节的指针（未找到：NULL）

/* memset：存储区填充：将字符c填充到mem的前n个字节（初始化内存） */
void *memset(void *mem, int c, size_t n);
// mem：指向待填充的内存块
// c：填充字符，以int形式传递的值（无符号字符）
// n：填充的字节数
// 返回值：指向存储区mem的指针

/* memcmp：存储区比较：比较两个存储区的前n个字节 */
int memcmp(const void *mem1, const void *mem2, size_t n);
// mem1：存储区1
// mem2：存储区2
// n：比较的字节数
// 返回值：<0（mem1 < mem2）；>0（mem1 > mem2）；=0（mem1 == mem2）

/* memcpy：存储区复制：从某存储区复制n个字节到另一个存储区 */
void *memcpy(void *dest, const void *src, size_t n);
// dest：目标存储区（类型强制转换void*）
// src：源存储区（类型强制转换void*）
// n：复制的字节数
// 返回值：指向目标存储区dest的指针

/* memmove：存储区复制（类似memcpy，但重叠内存块处理更安全） */
void *memmove(void *dest, const void *src, size_t n);
// dest：目标存储区（类型强制转换void*）
// src：源存储区（类型强制转换void*）
// n：复制的字节数
// 返回值：指向目标存储区dest的指针

// ---------------------- 字符串检索 ----------------------

/* strchr：字符串检索：检索字符串前n个字节中首次出现字符c的位置 */
char *strchr(const char *str, int c);
// str：字符串
// c：检索字符，以int形式传递的值（无符号字符）
// 返回值：指向首次匹配字符的位置（未找到：NULL）

/* strrchr：字符串检索：检索字符串最后一次出现字符c的位置 */
char *strrchr(const char *str, int c);
// str：字符串
// c：检索字符，以int形式传递的值（无符号字符）
// 返回值：指向最后一次匹配字符的位置（未找到：NULL）

/* strpbrk：字符串检索：检索str1字符串中首次出现str2中字符的位置 */
char *strpbrk(const char *str1, const char *str2);
// str1：字符串
// str2：包含检索字符的字符串（列表）
// 返回值：str1中首次匹配str2中字符的位置（未找到：NULL）

/* strspn：字符串检索：检索str1字符串中首次未找到str2中字符的下标（位置-1？） */
size_t strspn(const char *str1, const char *str2);
// str1：字符串
// str2：包含检索字符的字符串（列表）
// 返回值：str1中首次未匹配字符的下标

/* strcspn：字符串检索测距：检索str1字符串开头到首次匹配到str2中字符的距离 */
size_t strcspn(const char *str1, const char *str2);
// str1：字符串
// str2：包含检索字符的字符串（列表）
// 返回值：str1开头到首次匹配字符的距离

// ---------------------- 字符串间 ----------------------

/* strcpy, strncpy：字符串复制 */
char *strcpy(char *dest, char *src);
char *strncpy(char *dest, char *src, size_t n);
// dest：目标数组/字符串
// src：源字符串
// n：复制的最大字符数
// 返回值：最终复制的字符串

/* strcat, strncat：字符串连接：将src追加到dest后面 */
char *strcat(char *dest, char *src);
char *strncat(char *dest, char *src, size_t n);
// dest：目标数组（包含字符串，且足够容纳追加后的字符串，包括额外的空字符）
// src：源字符串（覆盖dest结尾处的'\0'）
// n：追加的最大字符数
// 返回值：指向最终的目标字符串dest的指针

/* strcmp, strncmp：字符串比较 */
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t n);
// str1：字符串1
// str2：字符串2
// n：比较的最大字符数
// 返回值：<0（str1 < str2）；>0（str1 > str2）；=0（str1 == str2）

/* strcoll：字符串比较（LC_COLLATE：字符排序规则） */
int strcoll(const char *str1, const char *str2);
// str1：字符串1
// str2：字符串2
// 返回值：<0（str1 < str2）；>0（str1 > str2）；=0（str1 == str2）

/* strxfrm：字符串转换（LC_COLLATE：字符排序规则） */
size_t strxfrm(char *dest, const char *src, size_t n);
// dest：目标数组/字符串（参数=0为NULL）
// src：源字符串（根据LC_COLLATE转换）
// n：转换的最大字符数
// 返回值：被转换字符串的长度（不包含空结束字符）

/* strstr：字符串子串查找 */
char *strstr(const char *str1, const char *str2);
// str1：被检索的字符串
// str2：子串
// 返回值：str1首次出现str2子串的位置（未找到：NULL）

/* strtok：字符串分解 */
char *strtok(char *str, const char *delim);
// str：字符串
// delim：包含分解字符的字符串（列表）
// 返回值：被分解的首个子字符串（未找到：NULL）

// ---------------------- 字符串其他 ----------------------

/* strlen：字符串长度计算：计算字符串的长度（截止到空结束字符前） */
size_t strlen(const char *str);
// str：字符串
// 返回值：字符串的长度（不包含空结束字符）

/* strerror：字符串错误搜索：根据错误号搜索错误消息 */
char *strerror(int errnum);
// errnum：错误号（通常为errno）
// 返回值：指向错误字符串的指针（描述错误号errnum）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * assert.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 诊断函数 ----------------------

/* assert：诊断 */
void assert(int expression);
// expression：变量/表达式
// 结果：TRUE（通过）；FALSE（中止，并在stderr显示错误信息）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * ctype.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 字符类 ----------------------

// 数字：{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
// 十六进制数字：{ 0 1 2 3 4 5 6 7 8 9 A/a B/b C/c D/d E/e F/f }
// 小写字母：{ a b c d e f g h i j k l m n o p q r s t u v w x y z }
// 大写字母：{ A B C D E F G H I J K L M N O P Q R S T U V W X Y Z }
// 字母/字母字符：{ 小写字母 大写字母 }
// 字母数字字符：{ 数字 字母 }
// 标点符号字符：{ ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~ }
// 图形字符：{ 字母数字字符 标点符号字符 }
// 空格字符：{ 制表符 换行符 垂直制表符 换页符 回车符 空格符 }
// 空白字符：{ 空格符 制表符 }
// 可打印字符：{ 图形字符 空格字符 }
// 控制字符：{ 000-037 177（DEL） } // ASCII

// ---------------------- 检测字符函数 ----------------------

/* isalnum：检测是否为字母数字字符 */
int isalnum(int c);
// c：检测字符（int值必须是EOF或表示无符号字符）
// 返回值：非0（失败：0）

/* isalpha：检测是否为字母 */
int isalpha(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* isupper：检测是否为大写字母 */
int isupper(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* islower：检测是否为小写字母 */
int islower(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* iscntrl：检测是否为控制字符 */
int iscntrl(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* isdigit：检测是否为数字 */
int isdigit(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* isgraph：检测是否为图形字符 */
int isgraph(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* isprint：检测是否为可打印字符 */
int isprint(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* ispunct：检测是否为标点符号字符 */
int ispunct(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* isspace：检测是否为空白字符 */
int isspace(int c);
// c：检测字符
// 返回值：非0（失败：0）

/* isxdigit：检测是否为十六进制数字 */
int isxdigit(int c);
// c：检测字符
// 返回值：非0（失败：0）

// ---------------------- 转换字符函数 ----------------------

/* tolower：将大写字母转换为小写字母 */
int tolower(int c);
// c：转换字符
// 返回值：c的小写字母（c非字母：保持不变）

/* toupper：将小写字母转换为大写字母 */
int toupper(int c);
// c：转换字符
// 返回值：c的大写字母（c非字母：保持不变）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * errno.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

extern int errno        // 错误事件
EDOM                    // 域错误，输入参数超出数学函数定义的域
ERANGE                  // 范围错误，输入参数超出数学函数定义的范围


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * float.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 浮点数 ----------------------

(+/-) p * b^e
// p：精度precision，基数b的有效位数
// b：基数base
// e：指数exponent

// ---------------------- 变量 && 宏 ----------------------

FLT_ROUNDS                    // 浮点数舍入模式（-1 无法确定；0 趋于0；1 最近值；2 趋于+∞；3 趋于-∞）
FLT_RADIX                     // 指数表示的基数（2 二进制；10 十进制；16 十六进制）
(FLT/DBL/LDBL)_MANT_DIG       // FLT_RADIX基数中位数（FLT float；DBL double；LDBL long double）
(FLT/DBL/LDBL)_DIG            // 基数为10时，舍入后不改变表示十进制数字的最大值
(FLT/DBL/LDBL)_MIN_EXP        // 基数为FLT_RADIX时，指数的最小负整数值
(FLT/DBL/LDBL)_MIN_10_EXP     // 基数为10时，指数的最小负整数值
(FLT/DBL/LDBL)_MAX_EXP        // 基数为FLT_RADIX时，指数的最大整数值
(FLT/DBL/LDBL)_MAX_10_EXP     // 基数为10时，指数的最大整数值
(FLT/DBL/LDBL)_MAX            // 最大的有限浮点值
(FLT/DBL/LDBL)_EPSILON        // 可表示的最小有效数字
(FLT/DBL/LDBL)_MIN            // 最小的浮点值


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * limits.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

CHAR_BIT              // 8，一个字节的比特数
SCHAR_MIN             // -128，char的最小值
SCHAR_MAX             // 127，char的最大值
UCHAR_MAX             // 255，unsigned char的最大值
CHAR_MIN              // 0，char的最小值（char表示负值，则=SCHAR_MIN）
CHAR_MAX              // 127，char的最大值（char表示负值，则=SCHAR_MAX）
MB_LEN_MAX            // 1，多字节字符中的最大字节数
SHRT_MIN              // -32768，short的最小值
SHRT_MAX              // +32767，short的最大值
USHRT_MAX             // 65535，unsigned short的最大值
INT_MIN               // -2147483648，int的最小值
INT_MAX               // 2147483647，int的最大值
UINT_MAX              // 4294967295，unsigned int的最大值
LONG_MIN              // -9223372036854775808，long的最小值
LONG_MAX              // 9223372036854775807，long的最大值
ULONG_MAX             // 1.8446744e+19，unsigned long的最大值


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * locale.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

LC_ALL             // 设置下面所有选项
LC_COLLATE         // 字符串比较，影响strcoll()和strxfrm()函数
LC_CTYPE           // 字符分类和转换，影响所有字符函数
LC_MONETARY        // 货币格式，影响localeconv()函数的货币信息
LC_NUMERIC         // 小数点分隔符，影响localeconv()函数的小数点格式化和信息
LC_TIME            // 日期和时间格式，影响strftime()函数
LC_MESSAGES        // 系统响应

// ---------------------- 函数 ----------------------

/* setlocale：设置或读取locale信息 */
char *setlocale(int category, const char *locale);
// category：设置LC_*
// locale：设置值（如果为NULL或""，则根据环境变量值来设置）
// 返回值：设置的不透明字符串（失败：NULL）

/* localeconv：设置或读取locale信息 */
struct lconv *localeconv(void);
// 返回值： lconv结构体对象


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * math.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

HUGE_VAL            // 函数结果不可为浮点数时，函数返回该值（特定很大的值）

// ---------------------- 数学函数 ----------------------

/* acos：反余弦函数 */
double acos(double x);
// x：介于[-1, +1]区间
// 返回值：x的反余弦（弧度表示[0, +pi]）

/* asin：正余弦函数 */
double asin(double x);
// x：介于[-1, +1]区间
// 返回值：x的正余弦（弧度表示[-pi/2, +pi/2]）

/* atan：反正切函数 */
double atan(double x);
// x：介于[-1, +1]区间
// 返回值：x的反正切（弧度表示[-pi/2, +pi/2]）

/* atan2：反正切函数 */
double atan2(double y, double x);
// y：y轴坐标
// x：x轴坐标
// 返回值：y/x的反正切（弧度表示[-pi, +pi]）

/* cos：余弦函数 */
double cos(double x);
// x：弧度表示的角度
// 返回值：x的余弦

/* cosh：双曲余弦函数 */
double cosh(double x);
// x：弧度表示的角度
// 返回值：x的双曲余弦

/* cosh：正弦函数 */
double sin(double x);
// x：弧度表示的角度
// 返回值：x的正弦

/* sinh：双曲正弦函数 */
double sinh(double x);
// x：弧度表示的角度
// 返回值：x的双曲正弦

/* tanh：双曲正切函数 */
double tanh(double x);
// x：弧度表示的角度
// 返回值：x的双曲正切

/* exp：幂函数（e^x） */
double exp(double x);
// x：幂
// 返回值：e的x次幂的值

/* frexp：将浮点数分解成尾数和指数（x = 尾数 * 2^指数） */
double frexp(double x, int *exponent);
// x：待计算值
// exponent：指数
// 返回值：尾数

/* ldexp：计算浮点数乘以2的指数（x * 2^指数） */
double ldexp(double x, int exponent);
// x：待计算值
// exponent：指数
// 返回值：x乘以2的exponent次幂

/* log：自然对数（loge x） */
double log(double x);
// x：真数
// 返回值：x的自然对数（基数为e=271828...，无理数）

/* log10：常用对数（log10 x） */
double log10(double x);
// x：真数
// 返回值：x的常用对数（基数为e=10）

/* modf：将浮点数分解成整数和小数（浮点数 = 整数.小数） */
double modf(double x, double *integer);
// x：浮点数
// integer：整数
// 返回值：小数（小数点后的部分）

/* pow：幂函数（x^y） */
double pow(double x, double y);
// x：基数
// y：指数
// 返回值：x的y次幂

/* sqrt：平方根（x^2） */
double sqrt(double x);
// x：基数
// 返回值：x的平方根

/* ceil：向上取整（x.xx -> x.00+1） */
double ceil(double x);
// x：浮点数
// 返回值：>=x的最小整数值

/* fabs：绝对值（|x|） */
double fabs(double x);
// x：浮点数
// 返回值：x的绝对值

/* floor：向下取整（x.xx -> x.00） */
double floor(double x);
// x：浮点数
// 返回值：<=x的最大整数值

/* fmod：取余（y/x的余数） */
double fmod(double x, double y);
// x：分子
// y：分母
// 返回值：y/x的余数


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * setjmp.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

jmp_buf                            // 绕过正常的函数调用和返回规则
int setjmp(jmp_buf environment)    // 创建jmp_buf缓冲区并且初始化（保存环境），用于将来跳转回此处；setjmp（直接调用）返回0，longjmp返回非0

// ---------------------- 函数 ----------------------

/* longjmp：恢复最近一次调用setjmp()时保存的环境 */
void longjmp(jmp_buf environment, int value);
// environment：环境
// value：setjmp判断值


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * signal.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

sig_atomic_t               // int类型，信号变量，可作为原子实体访问
SIG_DFL                    // 默认信号
SIG_ERR                    // 错误信号
SIG_IGN                    // 忽视信号
SIGABRT                    // 程序异常终止
SIGFPE                     // 算数运算出错（除数为0/溢出）
SIGILL                     // 非法函数映象（非法指令）
SIGINT                     // 中断信号（CTRL+C）
SIGSEGV                    // 非法访问存储器（访问不存在的内存单元）
SIGTERM                    // 终止请求信号（本程序）

// ---------------------- 函数 ----------------------

/* signal：带有SIG参数的信号处理程序 */
void (*signal(int sig, void (*func)(int)))(int);
// sig：信号码，SIGXXX（见宏）
// func：处理函数或SIG_XXX（见宏）
// 返回值：返回signal之前的值（发生错误：SIG_ERR）

/* raise：生成信号 */
int raise(int sig);
// sig：信号码，SIGXXX（见宏）
// 返回值：0（失败：非0）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * stdarg.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

va_list                              // 可变参数
void va_start(va_list ap, last_arg)  // 初始化ap变量（va_XXX中最先被调用），last_arg是最后传给函数的已知固定参数
type va_arg(va_list ap, type)        // 检索变量类型为type的下一个参数，返回该参数
void va_end(va_list ap)              // 带有可变参数的函数返回（va_start->va_end）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * stddef.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

ptrdiff_t                               // 有符号整数类型，指针相减
size_t                                  // 无符号整数类型，sizeof结果
wchar_t                                 // 宽字符常量大小的整数类型
NULL                                    // 空指针常量的值
offsetof(type, member-designator)       // 结构成员相对于结构开头的字节偏移量（size_t），member-designator成员，type结构名称


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * time.h
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

// ---------------------- 变量 && 宏 ----------------------

size_t                       // 无符号整数类型，sizeof结果
clock_t                      // 存储处理器时间的类型
time_t is                    // 存储日历时间的类型
struct tm                    // 存储日期时间的类型
// struct tm {
//   int tm_sec;         秒，[0-59]
//   int tm_min;         分，[0-59]
//   int tm_hour;        小时，[0-23]
//   int tm_mday;        月的第几天，[0-31]
//   int tm_mon;         月，[0-11]
//   int tm_year;        自1900年起的年数，年=1900+tm_year
//   int tm_wday;        周的第几天，[0-6]
//   int tm_yday;        年的第几天，[0-365]
//   int tm_isdst; };    夏令时
NULL                         // 空指针常量的值
CLOCKS_PER_SEC               // 处理器时钟个数/秒

// ---------------------- 时间测算函数 ----------------------

/* time：测算1970/1/1以来持续时间的秒数 */
time_t time(time_t *timer);
// timer：指向存储日历时间的对象的指针，不为空可被存储（同返回）
// 返回值：日历时间（1970/1/1以来持续时间的秒数）

/* clock：测算程序执行所使用的时间（处理器时钟） */
clock_t clock(void);
// 返回值：处理器时钟所用时间（秒=该时间/CLOCKS_PER_SEC，失败：-1）

/* difftime：测算两日历时间之间相差的秒 */
double difftime(time_t time1, time_t time2);
// time1：日历结束时间
// time2：日历开始时间
// 返回值：time1 - time2

// ---------------------- 时间转换函数 ----------------------

/* asctime：日期时间 -> 日期和时间 */
char *asctime(const struct tm *timeptr);
// timeptr：指向存储日期时间的结构体的指针
// 返回值：Www Mmm dd hh:mm:ss yyyy（Www周/Mmm月/dd日/hh时/mm分/ss秒/yyyy年）

/* ctime：日历时间 -> 日期和时间 */
char *ctime(const time_t *timer);
// timer：指向存储日历时间的对象的指针
// 返回值：Www Mmm dd hh:mm:ss yyyy

/* gmtime：日历时间 -> 日期时间 */
struct tm *gmtime(const time_t *timer);
// timer：指向存储日历时间的对象的指针
// 返回值：日期时间（协调世界时UTC/格林尼治标准时间GMT）

/* localtime：日历时间 -> 日期时间 */
struct tm *localtime(const time_t *timer);
// timer：指向存储日历时间的对象的指针
// 返回值：日期时间（本地时区）

/* mktime：日期时间 -> 日历时间 */
time_t mktime(struct tm *timeptr);
// timeptr：指向存储日期时间的结构体的指针
// 返回值：日历时间（失败：-1）

/* strftime：日期时间 -> 自定义格式化时间 */
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr);
// str：指向目标数组的指针，存储被复制的字符串
// maxsize：被复制到str的最大字符数
// format：字符串（普通字符和特殊格式说明符的任何组合）
// timeptr：指向存储日期时间的结构体的指针
// 返回值：0（若str <= 实际含空结束字符的size，返回被复制到str的字符总数，不含空结束字符）
