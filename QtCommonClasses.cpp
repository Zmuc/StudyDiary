————————————————————————————————————————————————————————————————————————————————————————
/* 基本类 */
————————————————————————————————————————————————————————————————————————————————————————


//@ QtCore::QChar：表示一个字符的类，内部用2个字节的Unicode编码来表示一个字符
————————————————————————————————————————————————————————————————————————————————————————
// 构造：
QChar();              // 构造一个空字符，即'\0'
QChar(char ch);       // 由字符数据ch构造
QChar(uchar ch);      // 由无符号字符数据ch构造
QChar(ushort code);   // 由无符号短整形数据code构造，code是Unicode编码
QChar(short code);    // 由短整形数据code构造
QChar(uint code);     // 由无符号整型数据code构造
QChar(int code);      // 由整型数据code构造

// 字符判断：
bool isDigit() const;       // 判断是否是十进制数字（'0'到'9'）
bool isLetter() const;      // 判断是否是字母
bool isNumber() const;      // 判断是否是数字，包括正负号、小数点等
bool isLetterOrNumber();    // 判断是否是字母或数字
bool isLower() const;       // 判断是否是小写字母
bool isUpper() const;       // 判断是否是大写字母
bool isNull() const;        // 判断是否是空子符'\0'
bool isPrint() const;       // 判断是否是可打印字符
bool isSpace() const;       // 判断是否是分隔符，包括空格等

// 数据转换：
char toAscii() const;      // 得到字符的ASCII码
QChar toLower() const;     // 转换成小写字母
QChar toUpper() const;     // 转换成大写字母
ushort unicode() const;    // 得到Unicode编码

// 字符比较：
bool operator != (QChar c1, QChar c2);   // 判断 c1 是否不等于   c2
bool operator < (QChar c1, QChar c2);    // 判断 c1 是否小于     c2
bool operator <= (QChar c1, QChar c2);   // 判断 c1 是否小于等于  c2
bool operator == (QChar c1, QChar c2);   // 判断 c1 是否等于     c2
bool operator > (QChar c1, QChar c2);    // 判断 c1 是否大于     c2
bool operator >= (QChar c1, QChar c2);   // 判断 c1 是否大于等于  c2


//@ QtCore::QString：表示字符串的类，内部采用Unicode编码
————————————————————————————————————————————————————————————————————————————————————————
// 构造：
Qstring();                              // 构造空字符串   
QString(QChar ch);                      // 由QChar对象ch构造   
QString(const QChar *pch, int size);    // 由QChar数组pch构造，size是数组大小   
QString(const QString &obj);            // 拷贝构造函数   
QString(const char *str);               // 由字符串str构造，str是一个普通字符串

// 字符串判断：
bool isEmpty() const;    // 判断是否为空字符串

// 字符串转换数值：
double toDouble(bool *ok =& nbsp;0) const;                          // 转换为double，高精度浮点数
float toFloat(bool *ok =& nbsp;0) cosnt;                            // 转换为float，浮点数
int toInt(bool *ok, int base =& nbsp;10) const;                     // 转换为int，整型数
long toLong(bool *ok, int base =& nbsp;10) cosnt;                   // 转换为long，长整型
short toShort(bool *ok, int base =& nbsp;10) const;                 // 转换为short，短整型
uint toUInt(bool *ok =& nbsp;0; int base = 10) const   & nbsp;      // 转换为unsigned int，无符号整型数
ulong toLong(bool *ok =& nbsp;0, int base = 10) const;  & nbsp;     // 转换为unsigned long，无符号长整型数
ushort toUShort(bool *ok =& nbsp;0, int base = 10) const;  & nbsp;  // 转换为unsigned short，无符号短整型数

// 数值转换字符串（改变自身的值）：
QString &setNum(int n, int base =& nbsp;10);                                       // 整型数   
QString &setNum(uint n, int base =& nbsp;10);                                      // 无符号整型数   
QString &setNum(long n, int base =& nbsp;10);                                      // 长整型   
QString &setNum(ulong n, int base =& nbsp;10);                                     // 无符号长整型数   
QString &setNum(short n, int base =& nbsp;10);                                     // 短整型数   
QString &setNum(ushort n, int base =& nbsp;10);                                    // 无符号短整型数   
QString &setNum(double n, char format =& nbsp;'g', int precision = 6);   & nbsp;   // 高精度浮点数   
QString &setNum(float n, char format =& nbsp;'g', int precision = 6);   & nbsp;    // 浮点数

// 数值转换字符串（返回临时对象）：
QString number(int n, int base = 10);  // 整型数（其他数值类型同上）

// 大小写转换：
QString toLower() const;  // 转换为小写
QString toUpper() const;  // 转换为大写

// 字符串比较(返回bool型)：
bool operator <  (StringType other) const;                     // 比较是否小于 other
bool operator <=& nbsp; (const char *s1, const QString &s2) ;  // 比较s1是否小于等于s2
bool operator ==& nbsp; (StringType other) const;              // 比较是否等于 other
bool operator >  (StringType other) constt;                    // 比较是否大于 other
bool operator >=& nbsp; (StringType other) const;              // 比较是否大于等于 other
bool operator !=& nbsp; (StringType other) const;              // 比较是否不等于 other
//StringType指的是（const QString &）或（const char *）

// 比较两个QString对象（返回int型）：
int compare(const QString &s1, const QString &s2, Qt::CaseSensitivity cs = Qt::CaseSensitive);
//参数表示：Qt::CaseInsensitive表示对大小写不敏感；Qt::Casesensitive表示对大小写敏感
//返回值含义：大于0表示s1>=s2；等于0表示s1=s2；小于0表示s1<=s2

// 查找目标字符或字符串是否存在：
bool contains(const QString &str, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;
bool contains(cosnt ch, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;

// 查找目标字符或字符串存在的次数：
int count(const QString &str, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;   
int count(QChar ch, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;   

// 顺序查找目标字符或字符串的位置：
int indexOf(const QString &str, int from = 0, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;   
int indexOf(QChar ch, int from = 0, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;
//from：表示查找起点，负数-i表示倒数第i个字符。
//返回值含义：查找到的目标字符或字符串的位置，如果没有找到则返回-1。 

// 反序查找目标字符或字符串的位置：
int lastIndexOf(const QString &str, int from = -1, Qt::CaseSensitivity cs = Qt::CaseSensitive) const;   
int lastIndexOf(QChar ch, int from = -1, Qt::CaseSensitivity cs = Qt::CaseSensitive) const

// 字符串复制：
QString &operator =& nbsp; (const QString &other);     // 复制另外一个QString对象
QString &operator =& nbsp; (const char *str);          // 复制普通字符串
QString &operator =& nbsp; (char ch);                  // 复制字符
QString &operator =& nbsp; (QChar ch);                 // 复制QChar类对象

// 字符串接续：
QString &append(const QString &str);     // 接续QString对象
QString &append(const char *str);        // 接续普通字符串
QString &append(QChar ch);               // 接续QChar对象
QString &operator +=& nbsp; (const QString &other);              // 接续QString对象   
QString &operator += (const char *str);                          // 接续普通字符串
QString &operator += (char ch);                                  // 接续字符型数据
QString &operator += (QChar ch);                                 // 接续QChar对象
const QString operator+(const QString &s1, const QString &s2);   // 拼接两个字符或字符串，返回临时对象

// 字符串首添：
QString &prepend(const QString &str);       // 在前面添接QString对象
QString &prepend(const char *str);          // 在前面添接普通字符串
QString &prepend(QChar ch);                 // 在前面添接QChar对象

// 字符串插入：
QString &insert(int position, const QString &str);             // 插入QString对象
QString &insert(int position, const QChar *pch, int size);     // 插入QChar数组
QString &insert(int position, QChar ch);                       // 插入QChar对象
//position：插入位置

// 字符串中按位置删除：
QString &remove(int position, int n);   // 移除QString对象中从位置position开始的n个字符

// 字符串删除制定字符或字符串：
QString &remove(QChar ch, Qt::CaseSensitivity cs = Qt::CaseSensitive);             // 删除QChar对象
QString &remove(const QString &str, Qt::CaseSensitivity cs = Qt::CaseSensitive);   // 删除QString对象

// 字符串替换：
QString &replace(int position, int n, const QString &after);         // QString对象
QString &replace(int position, int n, const QChar *pch, int size);   // QChar数组
QString &replace(int opsition, int n, QChar after);                  // QChar对象
QString &replace(QChar ch, cosnt QString &after, Qt::CaseSensitivity cs =& nbsp;Qt::CaseSensitive);  // QChar替换为QString   

// 清空QString对象的内容：
void clear();  // 清空

// 截断QString对象：
void truncate(int position);  // 从位置position向后截断，位置从0开始编号
void chop(int n);             // 截掉最后的n个字符
QString trimmed() const;      // 截去QString对象中头部和尾部的空白字符
QString simlified() const;    // 截去QString对象中头部和尾部的空白字符,并将中间连续多个空白字符全部替换成一个空格
//空白字符：空格、回车、换行、制表符等字符

// 获得QString子字符串（返回临时对象）：
QString left(int n) const;                      // 得到左边n个字符构成的子字符串
QString right(int n) const;                     // 得到右边n个字符构成的子字符串
QString mid（int position, int n = -1） const;   // 从中间得到子字符串

// 根据下标得到某个位置上的字符：
const QChar at(int position) const;             // at
const QChar operator[] (int position) const;    // 操作符[]，类似于对一个字符数组的操作
QCharRef operator[] (int position);             // 结合上面操作符[]取字符，返回的QCharRef类是一个辅助类，对它的修改将反映到原字符串中去

// 计算QString对象中字符的个数：
int size() const;
int length() const;
//字符的个数并不一定等于字节数


//@ QtCore::QPoint：表示一个坐标点，是一个整型的横坐标和一个整型的纵坐标的组合
————————————————————————————————————————————————————————————————————————————————————————
// 构造：
QPoint();                // 构造横纵坐标均为0的QPoint对象
QPoint(int x, int y);    // 构造横纵坐标分别为x和y的QPont对象

// 得到QPoint对象的横纵坐标的引用：
int x() const;    // 得到横坐标，只读
int y() const;    // 得到纵坐标，只读
int &rx();        // 得到横坐标的引用，可以通过它们直接修改QPoint
int &ry();        // 得到纵坐标的引用，可以通过它们直接修改QPoint

// 设置QPoint对象的横纵坐标：
void setX(int x); // 设置横坐标为x
void setY(int y); // 设置纵坐标为y

// 数值操作：
QPoint &operator+=(const QPoint &point);                        // 加赋值
QPoint &operator-=(const QPoint &point);                        // 减赋值
cosnt QPoint operator+ (const QPoint &p1, const QPoint &p2);    // 加法
const QPoint operator- (const QPoint &p1, const QPoint &p2);    // 减法
const QPoint operator- (const QPoint &point);                   // 取负数

// 判断：
bool operator== (const QPoint &p1, const QPoint &p2);        // 判断是否相等
bool operator!= (const QPoint &p1, const QPoint);            // 判断是否不等


//@ QtCore::QSize：表示一个矩形区域的大小，由一个整型的宽度和整型的高度组合而成
————————————————————————————————————————————————————————————————————————————————————————
// 构造：
QSize();                         // 构造一个非法的QSize对象
QSize(int width, int height);    // 构造宽度为width，高度为height的QSize对象

// 设置宽高：
void setWidth(int width);      // 设置宽度
void setHeight(int height);    // 设置高度

// 获得宽高：
int width() const;   // 获得宽度
int height() const;  // 获得高度

// 其他操作符相关类似QPoint


//@ QtGui::QFont：表示字体
————————————————————————————————————————————————————————————————————————————————————————
// 构造：
QFont();   // 由应用程序的默认字体构造新字体对象   
QFont(const QString &family, int pointSize = -1, int weight = -1, bool italic = false);
//family: 字体的名称 
//pointSize: 字体点大小，如果这个参数小于等于0，则自动设为12
//weight: 字体的粗细
//italic: 字体是否为斜体

// 获得及设置属性：
QString family() const;                    // 名称
void setFamily(const QString &family); 
int pointSize() const;                     // 点大小
void setPointSize(int pointSize);
int pixelSize() const;                     // 像素大小
void setPixelSize(int pixelSize); 
int weight() const;                        // 粗细
void setWeight(int weight); 
bool bold() const;                         // 是否粗体
void setBold(bool enable); 
bool italic() const;                       // 是否斜体
void setItalic(bool enable); 
bool underline() const;                    // 是否下划线
void setUnderline(bool enable); 

//@ QtGui::QPixmap：表示图像
————————————————————————————————————————————————————————————————————————————————————————
// 构造：
QPixmap();                        // 构造一个大小为0的空图像
QPixmap(const QSize &size);       // 构造大小为size的图像，但图像数据未初始化   
QPixmap(int width, int height);   // 等价于QPixmap(QSize(width, height));

// 从制定文件中加载图形并生成QPixmap对象：
QPixmap(const QString &filename, const char *format = 0, Qt::ImageConversionFlags flags = Qt::AutoColor);
//filename： 文件名
//format： 字符串，表示图像文件的格式，如果为0，将进行自动识别
//flags：表示颜色的转换模式，如果图像文件加载失败则产生空图像，这里flags参数有以下取值：
// 1)Qt::AutoColor：由系统自动决定
// 2)Qt::ColorOnly：彩色模式
// 3)Qt::MonoOnly：单色模式

// 图像参数：
int depth() const;     // 颜色深度，既每像素所占的比特数
int width() const;     // 图像宽度，单位是像素
int height() const;    // 图像高度，单位是像素
QSize size() cosnt;    // 图像的大小，即 QSize(width(), height());
QRect rect() const;    // 图像的矩形区域，即 QRect(QPoint(0,0),size());

// 加载图像：
bool load(const QString &filename, const char *fornat = 0, Qt::ImageCoversionFlags flags = Qt::AutoColor);
//从文件中加载图像，参数同构造

// 保存图像：
bool save(const QString &filename, const char *format = 0, int quality = -1) const;
//保存图像到文件
//filename：文件名
//format：字符串，表示图像文件的格式，如果为0，将根据文件名的后缀自动确定文件格式
//quality：对于有损压缩的文件格式来说，它表示图像保存的质量，质量越低压缩率越大。取值范围为0～100，-1 表示采用默认值
//返回值：true 表示保存成功，false 表示保存失败

// 判断:
bool isNull() const;     // 判断是否为空图像


//@ QtGui::Qlcon：表示一系列图像的组合
————————————————————————————————————————————————————————————————————————————————————————
// 构造：
QIcon();                          // 构造一个空图像构成的图标
QIcon(const QPixmap &pixmap);     // 从 Pixmap 对象构造函数
QIcon(const QString &filename);   // 从图像文件构造图标

// 添加图像：
void addFile(const QString &filename, const QSize &size = QSize(), Mode mode = Normal, State state = Off);
//从图像文件中向 QIcon 对象添加图像
//filename：文件名
//size：指定大小
//mode：指定使用模式，即窗口在何种状态下使用这个图像
//state：指定使用状态
//Mode为QIcon类的成员类型，有以下取值：
// 1)QIcon::Normal：窗口为使能状态，但未激活
// 2)QIcon::Disabled：窗口为禁用状态
// 3)QIcon::Active：窗口为激活状态
// 4)QIcon::Selected：窗口被选中
//State为QIcon类的成员类型，有以下取值：
// 1)QIcon::Off：窗口在关状态
// 2)QIcon::On：窗口在开状态


// 将QPixmap对象添加到QIcon对象：
void addPixmap(const QPixmap &pixmap, Mode mode = Normal, State state = Off);

// 获取 QIcon 对象中的图像：
QPixmap pixmap(const QSize &size, Mode  mode = Normal, State state = Off) const;

// 判断：
bool isNull() const;    // 判断是否为空图像构成的图标


————————————————————————————————————————————————————————————————————————————————————————
/* 窗口类 */
————————————————————————————————————————————————————————————————————————————————————————


//@ QWidget：表示一般窗口，其他窗口类都是从QWidget类继承，而QWidget类则是同时继承QObject类和QPaintDevice类
————————————————————————————————————————————————————————————————————————————————————————
// 构造：
QWidget(QWidget *parent = 0, Qt::WindowFlags f = 0);
//parent：指向父窗口，如果这个参数为0，则窗口就成为一个顶级窗口 
//f：构造窗口的标志，主要用于控制窗口的类型和外观等，有以下常用值：
// 1)Qt::FramelessWindowHint：没有边框的窗口
// 2)Qt::WindowStaysOnTopHint：总是最上面的窗口
// 3)Qt::CustomizeWindowHint：自定义窗口标题栏，以下标志必须与这个标志一起使用才有效，否则窗口将有默认的标题栏
// 4)Qt::WindowTitleHint：显示窗口标题栏
// 5)Qt::WindowSystemMenuHint：显示系统菜单
// 6)Qt::WindowMinimizeButtonHint：显示最小化按钮
// 7)Qt::WindowMaximizeButtonHint：显示最大化按钮
// 8)Qt::WindowMinMaxbuttonHint：显示最小化按钮和最大化按钮
// 9)Qt::WindowCloseButtonHint：显示关闭按钮


// 判断是否为独立窗口：
bool isWindow() const;     // 判断是否为独立窗口
//独立窗口定义如下：
//窗口构造时如果有Qt::Window标志，即是独立窗口，否则就是依附于其他独立窗口的窗口部件
//顶级窗口一定是独立窗口，但独立窗口不一定是顶级的，它可以有父窗口，当父窗口被析构时随之被析构
//独立窗口一般有自己的外边框和标题栏，可以移动、改变大小等操作

// 得到窗口部件所在的独立窗口：
QWidget *window() const;   // 所得所在的独立窗口
//如果窗口本身就是独立窗口，那么得到的就是自己

// 得到窗口的父窗口：
QWidget *parentWidget() const;   // 得到父窗口

// 窗口标题：
QString windowTitle() const;                 // 获得窗口标题
void setWindowTitle(const QString &text);    // 设置窗口标题为text

// 几何参数（窗口的大小和位置）：
const QRect &geometry() const;                 // 获取客户区几何参数
void setGeometry(int x, int y, int w, int h);  // 设置客户区几何参数
void setGeometry(const QRect &rect);           // 设置客户区几何参数
QRect frameGeometry() const;                   // 获取外边框几何参数
//窗口有两套几何参数：窗口外边框所占的矩形区域，窗口客户区所占的矩形区域（窗口客户区指窗口中去除边框和标题栏用来显示内容的区域）
//改变大小和位置可能会触发：窗口移动事件QMoveEvent（函数moveEvent）和窗口改变大小事件QResizeEvent（函数resizeEvent）
QPoint pos() const;              // 获得窗口左上角的坐标(外边框几何参数)
QSize size() const;              // 窗口大小 （客户区几何参数）
int x() const;                   // 窗口左上角横坐标 （外边框几何参数）
int y() const;                   // 窗口左上角纵坐标 （外边框几何参数）
int height() const;              // 窗口高度 （客户区几何参数）
int width() const;               // 窗口宽度 （客户区几何参数）
QSize frameSize() const;         // 获得窗口大小 （外边框几何参数）
void move(int x, int y);         // 将窗口左上角移动到坐标（x, y）处 （外边框几何参数）
void move(const QPoint &pos);    // 将窗口左上角移动到pos处 （外边框几何参数）
void resize(int w, int h);       // 将窗口的宽度改为w，高度改为h （客户区几何参数）
void resize(const QSize &size);  // 将窗口的大小改为size （客户区几何参数）
QRect rect() const;              // 获取窗口区域 （相对于窗口自己的客户区，即横纵坐标永远为0）

// 可见性与隐藏：
bool isVisible() const;                  // 判断窗口是否可见
bool isHidden() const;                   // 判断窗口是否隐藏
virtual void setVisible(bool visible);   // 设置窗口是否隐藏
void setHidden(bool hidden);             // 等价于setvisible(!hidedn);
// 1)隐藏的窗口一定是不可见的
// 2)非隐藏的窗口在它的父窗口可见的情况下也是可见的
// 3)非隐藏的顶级窗口是可见的
void show();   // 显示窗口，等价于setVisible(true);
void hide();   // 隐藏窗口，等价于setHidden(true);
//setVisible和setHidden也是槽，一般并不直接使用，而是使用上述两个槽
//窗口显示时，将发送QShowEvent事件（函数showEvent）；窗口隐藏时，将发送QHideEvent事件（函数hideEvent） 

// 窗口状态：
bool isMinimized() const;    // 判断窗口是否为最小化
bool isMaximized() const;    // 判断窗口是否为最大化
bool isFullScreen() const;   // 判断窗口是否为全屏
void showMinimized();        // 以最小化方式显示窗口，这是一个槽
void showMaximized();        // 以最大化方式显示窗口，这是一个槽
void showFullScreen();       // 以全屏方式显示窗口，这是一个槽
void showNormal();           // 以正常方式显示窗口，这是一个槽
//全屏方式与最大化的区别在于：全屏方式下窗口的边框和标题栏消失，客户区占据整个屏幕
//窗口的各种状态仅对独立窗口有效，对窗口部件没意义
Qt::WindowStates windowState() const;                // 获取窗口状态
void setWindowState(Qt::WindowStates windowState);   // 设置窗口状态
//调用setWindowState 函数将使窗口变为隐藏状态
//Qt::WindowStates类型有取值如下，可通过“|”方式组合：
// 1)Qt::WindowNoState：无标志，正常状态
// 2)Qt::WindowMinimized：最小化状态
// 3)Qt::WindowMaxmized：最大化状态
// 4)Qt::WindowFullScreen：全屏状态
// 5)Qt::WindowActive：激活状态

// 使能状态（属性enabled）：
bool isEnabled() const;          // 获得窗口的使能状态
void setEnabled(bool enable);    // 设置窗口的使能状态，这是一个槽
void setDisabled(bool disabled); // 等价于setEnabled(!disable)，这是一个槽
//处于使能状态的窗口才能处理键盘和鼠标等输入事件，反之不能
//使能状态禁用一个窗口同时会使它的所有子窗口成为禁用状态
//窗口的使能状态可能影响外观（禁用状态的按钮文本本身为灰色）

// 激活状态（独立窗口）：
bool isActiveWindow() const;   // 判断窗口所在的独立窗口是否激活
void activateWindow();         // 设置窗口所在的独立窗口为激活状态
//当有多个独立窗口同时存在时，只有一个窗口能够处于激活状态，接收系统产生的键盘、鼠标等输入事件
//激活状态的独立窗口一般在堆叠层次最上面，除非其他窗口有总在最上面的属性

// 焦点（控制独立窗口内哪个部件可以接受键盘事件，同时刻只能有一个部件获得焦点）：
bool hasFocus() const;          // 判断窗口是否获得焦点
void setFocus();                // 使窗口获得焦点，这是一个槽
void clearFocus();              // 使窗口失去焦点
QWidget *focusWidget() const;   // 得到窗口内获得焦点的子窗口
//当窗口获得或失去焦点时，将发送QFocusEvent事件（函数forceInEvent和focusOutEvent）
bool hasEditfocus() const;                // 判断窗口是否有editFocus属性
void QWidget::setEditFocus(bool enable);  // 设置窗口的editFocus属性
//editFocus属性：专门用于嵌入式系统，因为嵌入式系统通常键盘较小，没有用于切换焦点的Tab键，所以使用上下方向键切换焦点
//如果窗口部件设置editFocus属性为true，则上下方向键就不再用于切换焦点，而是发送给这个窗口


// 捕获/释放键盘和鼠标等：
void grabKeyboard();        // 捕获键盘事件
void releaseKeyboard();     // 释放键盘事件
void grabMouse();           // 捕获鼠标事件
void releaseMouse();        // 释放鼠标事件
QWidget *keyboardGrabber(); // 得到正在捕获键盘事件的窗口
QWidget *mouseGrabber();    // 得到正在捕获鼠标事件的窗口
//捕获了键盘/鼠标事件的窗口将得到所有事件，而其他窗口必须等捕获键盘/鼠标事件的窗口释放后才能捕获
//对键盘事件和鼠标事件的捕获是相互独立的
//只有可见的窗口才能进行输入事件捕获

// 布局（属性layout）：
QLayout *layout() const;           // 获得顶级布局
void setLayout(QLayout *layout);   // 设置顶级布局

// 字体（属性font）：
const QFont &font() const;      // 获得字体
void setFont(const QFont &);    // 设置字体
//如果没有设置字体，则窗口自动使用父窗口的字体，顶级窗口则使用应用程序的默认字体

// 信号：
void destoryed(QObject *obj = 0);
//QOjbect类继承过来的信号：QObject对象析构时，先发射这个信号，然后才析构它的所有子对象

// 槽（其他常用）：
bool close();   // 关闭窗口
//如果窗口设置了Qt::WA_QuitOnClose属性，则窗口关闭时，其对象会被析构（大多数类型的窗口都默认设置了这个属性）
void lower();   // 降低窗口堆叠层次到最下面   
void raise();   // 提升窗口堆叠层次到最上面   

// 窗口事件：
virtual void closeEvent(QCloseEvent *event);    // 关闭
virtual void showEvent(QShowEvent *event);      // 显示
virtual void hideEvent(QHideEvent *event);      // 隐藏
virtual void moveEvent(QMoveEvent *evnet);      // 移动
//窗口旧坐标和新坐标（QMoveEvent事件）：
const QPoint &oldPos() const;   // 旧坐标
const QPoint &newPos() constl   // 新坐标
virtual void resizeEvent(QResizeEvent *event);  // 改变大小
//窗口旧大小和新大小（QResizeEvent事件）：
const QSize &oldSize() const;   // 旧大小
const QSize &newSize() const;   // 新大小

// 键盘事件：
virtual void keyPressEvent(QKeyEvent *event);    // 键按下
virtual void keyReleaseEvent(QKeyEvent *event);  // 键松开
int key() const;     // 得到键值（QKeyEvent类）

// 鼠标事件：
virtual void mousePressEvent(QMouseEvent *event);         // 鼠标键按下
virtual void mouseReleaseEvent(QMouseEvent *event);       // 鼠标键松开
virtual void mouseDoubleCllckEvent(QMouseEvent *event);   // 鼠标键双击
virtual void mouseMoveEvent(QMouseEvent *event);          // 鼠标移动
virtual void enterEvent(QEvent *event);                   // 鼠标进入窗口
virtual void leaveEvent(QEvent *event);                   // 鼠标离开窗口
virtual void wheelEvent(QWheelEvent *event);              // 鼠标滚轮移动
//关于鼠标的信息（QMouseEvent事件）：
const QPoint &pos() const;         // 得到鼠标坐标 （相对于接收事件的窗口）
int x()  const;                    // 得到鼠标横坐标 （相对于接收事件的窗口）
int y() const;                     // 得到鼠标纵坐标 （相对于接收事件的窗口）
const QPoint &globalPos() const;   // 得到鼠标坐标 （全局坐标）
int globalX() const;               // 得到鼠标横坐标 （全局坐标）
int globalY() const;               // 得到鼠标纵坐标 （全局坐标）
Qt::MouseButton button() const;    // 得到引起事件的鼠标键
Qt::MouseButtons buttons() const;  // 得到事件发生时的鼠标键状态
//Qt::MouseButton是一个枚举类型，取值如下：
// 1)Qt::NoButton：无键
// 2)Qt::LeftButton：左键
// 3)Qt::RightButton：右键
// 4)Qt::MidButton：中键
//鼠标移动事件QMouseEvent和button函数总是返回Qt::NoButton，但buttons函数返回值则是Qt::MouseButton类型的“|”组合，反映事件发生时鼠标键的按下状态
//关于滚轮的信息（QWheelEvent事件，成员函数几乎与QMountEvent事件相同，但少button函数，多两个函数）：
int delta() const;                       // 获得滚轮转动的角度   
Qt::Orientation orientationI() const;    // 获得滚轮转动的方向
//Qt::Orientation是一个枚举类型，以下取值如下： 
// 1)Qt::Horizontal：横向
// 2)Qt::Vertical：纵向

// 焦点事件:
virtual void focusInEvent(QFocusEvent *event);   // 获得焦点
virtual void focusOutEvent(QFocusEvent *event);  // 时取焦点
//接受或拒绝一个事件要调用QEvent类的成员函数:
event->accept();    // 接受事件
event->ignore();    // 拒绝事件
