/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * 文件I/O
 *   - 基于文件描述符的I/O操作（Linux基于文件的概念，所有对设备/文件的操作都使用文件描述符来进行）
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

/* open：打开/创建文件 */
int open(const char* path, int flag, int perms);
// #include <fcntl.h>
// path：被打开的文件
// flag：文件打开方式
//     - O_RDONLY：以只读方式打开文件
//     - O_WRONLY：以只写方式打开文件
//     - O_RDWR：以读写方式打开文件
//     - O_CREAT：文件不存在时创建（权限为perms）
//     - O_EXCL：使用O_CREAT且文件存在，返回错误消息
//     - O_NOCTTY：文件若为终端，则该终端不会被控制
//     - O_TRUNC：文件存在时清空数据，并设置文件大小为0
//     - O_APPEND：以添加方式打开文件，文件指针在文件末尾
// perms：被打开文件的权限（如0644）
// 返回值：文件描述符（失败：-1）

/* close：关闭被打开的文件 */
int close(int fd);
// #include <unistd.h>
// fd：文件描述符
// 返回值：0（失败：-1）

/* read：将从文件中读出的数据放到缓存区中 */
ssize_t read(int fd, void* buf, size_t count);
// #include <unistd.h>
// fd：文件描述符
// buf：缓存区
// count：指定读出字节数
// 返回值：读取的字节数（已到达文件：0；失败：-1）

/* write：向打开的文件写数据（从缓存区） */
ssize_t write(int fd, void* buf, size_t count);
// #include <unistd.h>
// fd：文件描述符
// buf：缓存区
// count：指定写入字节数
// 返回值：写入的字节数（失败：-1）

/* lseek：移动打开文件的文件指针 */
off_t lseek(int fd, off_t offset, int fromwhere);
// #include <unistd.h>
// fd：文件描述符
// offset：相对于fromwhere的偏移量（字节）
// fromwhere：offset开始位置
//     - SEEK_SET：从文件开头开始，非负
//     - SEEK_CUR：从文件指针处开始
//     - SEEK_END：从文件末尾开始
// 返回值：文件指针当前偏移量（失败：-1）

/* fcntl：文件锁 */
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd, struct flock * lock);
// #include <fcntl.h>
// fd：文件描述符
// cmd：操作指令
//     - F_DUPFD：用>=arg的最小文件描述符，复制fd
//     - F_GETFD：取得close-on-exec状态（FD_CLOEXEC=0，调用exec()相关函数时文件不会关闭）
//     - F_SETFD：设置close-on-exec状态（参数arg的FD_CLOEXEC位）
//     - F_GETFL：取得文件描述符状态（open()函数的flag参数）
//     - F_SETFL：设置文件描述符状态（参数arg的O_APPEND、O_NONBLOCK和O_ASYNC位）
//     - F_GETLK：取得文件锁定状态
//     - F_SETLK：设置文件锁定状态（struct flock的l_type值必须是F_RDLCK、F_WRLCK或F_UNLCK）
//     - F_SETLKW：同F_SETLK，无法建立锁定时会一直等待，直到锁定成功
// arg：操作指令参数
// lock：文件记录锁状态（struct flock）
// 返回值：根据cmd返回对应内容（成功：0；失败：-1）

/* flock：文件记录锁 */
struct flock {
    short int l_type;   // 锁定状态

    short int l_whence; // 位置
    off_t l_start;      // 偏移量，锁定区域起始：l_whence + l_start
    off_t l_len;        // 锁定区域长度
    pid_t l_pid;        // 锁定的进程
};
// #include <fcntl.h>
// l_type:
//     - F_RDLCK：共享锁（读）
//     - F_WRLCK：排斥锁（写）
//     - F_UNLCK：无锁（解锁）
// l_whence:
//     - SEEK_SET：文件开头
//     - SEEK_CUR：文件指针位置
//     - SEEK_END：文件末尾
// 整个文件加锁：l_whence = SEEK_SET; l_start = 0; l_len = 0;

/* select：监听一个/多个文件句柄的状态变化 */
int select(int fds_max, fd_set *read_fds, fd_set *write_fds, fd_set *except_fds, struct timeval *timeout);
// #include <sys/select.h>
// fds_max：监听的文件描述符集合中最大值+1
// read_fds：监听的可读文件描述符集合
// write_fds：监听的可写文件描述符集合
// except_fds：监听的异常处理文件描述符集合
// timeout：
//     - NULL：阻塞状态，当监听的文件描述符集合中某个发生变化时，返回结果并向下执行
//     - =0：非阻塞状态，无论文件描述符是否变化，执行后立即返回
//     - >0：超时时间，由阻塞状态 -> 非阻塞状态
// 返回值：准备好的文件描述符（超时：0；失败：-1）

/* FD_*：select()函数相关宏 */
FD_ZERO(fd_set *fds);              // 将fds（文件描述符集合）清空
FD_CLR(int fd, fd_set *fds);       // 将fd（文件描述符）从fds中删除
FD_SET(int fd, fd_set *fds);       // 将fd加入fds
FD_ISSET(int fd, fd_set *fds);     // 测试fd是否在fds中

/* timeval：时间 */
struct timeval {
    time_t tv_sec;     // 秒
    time_t tv_usec;    // 微秒
};
// #include <bits/types/struct_timeval.h>

/* poll：监听一个/多个文件句柄的状态变化 */
int poll(struct pollfd *fds, nfds_t fds_num, int timeout);
// #include <sys/poll.h>
// fds：监听的多个文件描述符
// fds_num：监听的文件描述符数目
// timeout：
//     - <0：阻塞状态，当监听的文件描述符集合中某个发生变化时，返回结果并向下执行
//     - =0：非阻塞状态，无论文件描述符是否变化，执行后立即返回
//     - >0：超时时间，由阻塞状态 -> 非阻塞状态
// 返回值：结构体pollfd中revents非0的文件描述符数目（超时：0；失败：-1）

/* pollfd：文件描述符 */
struct pollfd {
    int fd;           // 文件描述符
    short events;     // 监听的事件，用户设置
    short revents;    // 返回事件的结果，内核调用返回时设置
};
// #include <sys/poll.h>
// events:
//     - POLLIN（0x0001）：文件中有数据可读
//     - POLLPRI（0x0002）：文件中有紧急数据可读
//     - POLLOUT（0x0004）：文件中可写入数据
//     - POLLERR（0x0008）：文件中出现错误（只限于输出）
//     - POLLHUP（0x0010）：文件连接被断开（只限于输出）
//     - POLLNVAL（0x0020）：文件描述符非法（未指向成功打开的文件）

/* access：确定文件或文件夹的访问权限 */
int access(const char *path, int mode);
// #include <unistd.h>
// path：检测的文件或文件夹路径（可用相对路径）
// mode：判断访问权限
//     - R_OK：读
//     - W_OK：写
//     - X_OK：执行
//     - F_OK：是否存在
// 返回值：权限有效0（失败：-1）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * 多任务/多进程/多线程
 *   - 任务 = n 进程 = n × m 线程
 *   - 进程：系统资源分配和调度的最小单元
 *       - 内存：用户空间虚拟内存
 *       - 结构：所有进程都在进程链表（双向循环链表）中
 *           - init_task：描述符，位于链表头
 *           - task_struct：进程描述符，结构较大，每个结构体对应一个进程（完整描述）
 *               - state：进程状态（重要）
 *               - pid：进程标识符（重要）
 *       - 进程状态：
 *           - TASK_RUNNING：运行状态，进程处于运行中/队列中等待调度
 *           - TASK_STOPPED：暂停状态，进程被信号（SIGSTOP、SIGSTP、SIGTTIN、SIGTTOU）暂停
 *           - TASK_TRACED：跟踪状态，进程被调试器暂停（调试器进程监控执行进程）
 *           - EXIT_ZOMBIE：僵尸状态，进程运行结束但尚未被父进程回收（wait函数族），进程只在进程链表中保留位置，无可执行代码，不能被调度
 *           - EXIT_DEAD：退出状态，进程彻底被删除（由父进程回收）
 *           - TASK_INTERRUPTIBLE/TASK_UNINTERRUPTIBLE/TASK_KILLABLE：可中断/不可中断/可终止阻塞（睡眠）状态，进程等待事件发生/资源可用
 *       - 进程标识符：
 *           - 进程标识符PID唯一，用来标识进程
 *           - 新建进程PID = 前一个进程PID + 1（有上限）
 *           - PPID为父进程标识符
 *           - getpid()函数获取PID，getppid()函数获取PPID
 *   - 线程：处理器调度的最小单元
 *       - 内存：与其他线程（同一进程）共享父进程的内存空间和资源
 *       - 多线程遵循POSIX线程接口（pthread），使用libpthread.a，所以编译时加上-lpthread
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

/* fock：从已有进程（父）中创建新进程（子） */
pid_t fork(void);
// #include <unistd.h>
// 返回值：父进程中返回子进程PID（>0），子进程中返回0（失败：<0）

/* exec*：fork()出的子进程执行可执行文件 */
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char *const envp[]);
// #include <unistd.h>
// path：可执行文件路径
// file：可执行文件路径，可使用文件名在PATH环境变量中搜寻（p，path）
// arg：参数，逐个列举（l，list）
// argv[]：参数，构造指针数组（v，vector），必须以NULL作为结束标识符
// envp[]：指定进程所使用的环境变量（e，env）
// 返回值：执行成功无返回，因为调用进程的实体被刷新（失败：-1）

/* _exit：直接终止进程 */
void _exit(int status);
// #include <unistd.h>
// status：进程结束时的状态（0正常，非0异常）

/* exit：终止进程并处理I/O缓冲 */
void exit(int status);
// #include <stdlib.h>
// status：进程结束时的状态（0正常，非0异常）

/* wait：调用该函数的进程（父进程）阻塞，直到子进程结束或发出指定信号 */
pid_t wait(int *status);
// #include <sys/wait.h>
// status：整形指针，子进程结束时的状态
// 返回值：成功结束的子进程PID（失败：-1）

/* waitpid：阻塞调用进程（父进程）并等待 */
pid_t waitpid(pid_t pid, int *status, int opt);
// #include <sys/wait.h>
// pid：进程号，进程组号
//     - >0：等待PID为pid的子进程结束，不考虑其他子进程状态
//     - =-1：等待任意子进程结束（类似wait()函数）
//     - =0：等待与调用进程（父进程）GID相等的任意子进程结束
//     - <-1：等待GID为pid的任意子进程（同组）结束
// status：整形指针，子进程结束时的状态
// opt：选项
//     - WNOHANG：pid对应的子进程结束则返回进程号，未结束则返回0（waitpid()函数立即返回）
//     - WUNTRACED：pid对应的子进程进入暂停状态，返回其状态（waitpid()函数立即返回）
//     - 0：不使用选项
// 返回值：成功结束的子进程PID（失败：-1）

/* setsid：创建新会话组并使调用进程成为组长（拜托父进程的会话期、进程组和控制终端） */
pid_t setsid(void);
// #include <unistd.h>
// 返回值：进程组ID（失败：-1）
// 会话组（会话期） = n × 进程组 = n × m × 进程

/* pthread_create：创建线程 */
int pthread_create(pthread_t *newthread, pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg);
// #include <pthread.h>
// newthread：线程标识符/ID
// attr：线程属性（NULL为默认属性）
// start_routine：线程函数（函数指针，指向线程调用的函数）
// arg：线程函数的参数
// 返回值：0（失败：非0）

/* pthread_exit：退出线程 */
void pthread_exit(void *retval);
// #include <pthread.h>
// retval：线程结束后的返回值（可由pthread_join()获取）

/* pthread_join：线程等待 */
int pthread_join(pthread_t th, void **thread_return);
// #include <pthread.h>
// th：等待退出的线程ID
// thread_return：等待退出的线程的返回值（指针存储）
// 返回值：0（失败：非0）

/* pthread_cancel：线程取消 */
int pthread_cancel(pthread_t th);
// #include <pthread.h>
// th：要取消的线程ID
// 返回值：0（失败：非0）

/* pthread_self：获取线程标识符/ID */
pthread_t pthread_self(void);
// #include <pthread.h>
// 返回值：调用该函数的线程ID

/* pthread_cleanup_push：将清除函数压入清除栈 */
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
// #include <pthread.h>
// rtn：清除函数
// arg：清除函数的参数
// 新版本该函数可能为宏

/* pthread_cleanup_pop：将清除函数弹出清除栈 */
void pthread_cleanup_pop(int execute);
// #include <pthread.h>
// execute：弹出清除函数时是否执行
//     - 0：不执行
//     - 非0：执行
// 新版本该函数可能为宏

/* pthread_mutex_init：初始化互斥锁 */
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
// #include <pthread.h>
// mutex：互斥锁标识符
// mutexattr：互斥锁类型
//     - PTHREAD_MUTEX_INITIALIZER：快速互斥锁
//     - PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP：递归互斥锁
//     - PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP：检错互斥锁
// 返回值：0（失败：非0）

/* pthread_mutex_lock：互斥锁上锁 */
int pthread_mutex_lock(pthread_mutex_t *mutex);
// #include <pthread.h>
// mutex：互斥锁标识符
// 返回值：0（失败：-1）

/* pthread_mutex_trylock：互斥锁判断是否上锁 */
int pthread_mutex_trylock(pthread_mutex_t *mutex);
// #include <pthread.h>
// mutex：互斥锁标识符
// 返回值：0（失败：-1）

/* pthread_mutex_unlock：互斥锁解锁 */
int pthread_mutex_unlock(pthread_mutex_t *mutex);
// #include <pthread.h>
// mutex：互斥锁标识符
// 返回值：0（失败：-1）

/* pthread_mutex_destroy：消除互斥锁 */
int pthread_mutex_destroy(pthread_mutex_t *mutex);
// #include <pthread.h>
// mutex：互斥锁标识符
// 返回值：0（失败：-1）


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * 系统服务日志
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

/* openlog：打开系统日志服务的链接 */
void openlog(char *ident, int opt, int facility);
// #include <syslog.h>
// ident：字符串，每个消息都加入
// opt：选项
//     - LOG_PID：每条消息都包含PID
//     - LOG_CONS：系统日志服务无法接收消息的情况下将消息输出到终端
//     - LOG_ODELAY：延迟打开系统日志服务（等待第一个syslog()），默认
//     - LOG_NDELAY：立即打开系统日志服务
//     - LOG_NOWAIT：已弃用
//     - LOG_PERROR：将消息输出到stderr
// facility：指定消息类型
//     - LOG_KERN：内核
//     - LOG_USER：随机用户
//     - LOG_MAIL：邮件系统
//     - LOG_DAEMON：系统守护进程
//     - LOG_AUTH：安全认证
//     - LOG_SYSLOG：syslogd内部
//     - LOG_LPR：行打印
//     - LOG_NEWS：网络新闻
//     - LOG_UUCP：UUCP
//     - LOG_CRON：时钟时间
//     - LOG_AUTHPRIV：安全认证（私有）
//     - LOG_FTP：FTP
//     - LOG_LOCAL[0-7]：系统保留

/* syslog：向系统日志文件中写入信息 */
void syslog(int pri, char *fmt, ...);
// #include <syslog.h>
// pri：指定消息的重要性
//     - LOG_EMERG：系统不稳定（无法使用）
//     - LOG_ALERT：需要立即采取措施
//     - LOG_CRIT：严重错误Critical
//     - LOG_ERR：错误Error
//     - LOG_WARNING：警告Warning
//     - LOG_NOTICE：正常且重要Notice
//     - LOG_INFO：信息Info
//     - LOG_DEBUG：调试Debug
// fmt：字符串指针，表示消息的输出格式

/* closelog：关闭系统日志服务的链接 */
void closelog(void);
// #include <syslog.h>


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * 进程间通信
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

/* pipe：创建无名管道 */
int pipe(int fd[2]);
// #include <unistd.h>
// fd[2]：管道的两个文件描述符（fd[0] - 读；fd[1] - 写）
// 返回值：0（失败：-1）
// 管道位于内核，通过fork的子进程与父进程通信（fork继承管道）

/* popen：创建标准流管道 */
FILE *popen(const char *cmd, const char *mode);
// #include <stdio.h>
// cmd：字符串，传递给/bin/sh -c（shell）
// mode：模式
//     - r：连接cmd的标准输出
//     - w：连接cmd的标准输入
// 返回值：文件流指针FILE *（失败：-1）
// popen() = 创建管道 + fork子进程 + 关闭不必要的文件描述符 + 调用exec函数族 + 执行cmd命令

/* pclose：关闭标准流管道（必须配对popen） */
int pclose(FILE *stream);
// #include <stdio.h>
// stream：popen创建的文件流指针
// 返回值：popen执行进程的退出码（失败：-1）

/* mkfifo：创建有名管道 */
int mkfifo(const char *path, mode_t mode)
// #include <sys/stat.h>
// path：创建的管道（绝对路径）
// mode：模式
//     - O_RDONLY：读
//     - O_WRONLY：写
//     - O_RDWR：读写
//     - O_NONBLOCK：非阻塞
//     - O_CREAT：如果path不存在，则创建新的管道
//     - O_EXCL：如果O_CREAT时path存在，则返回错误消息
// 返回值：0（失败：-1）

/* SIGXXX：信号 */
// ISO C99
#define SIGINT          2       // 中断（INTR字符，通常是CTRL+C，默认终止前台进程）
#define SIGILL          4       // 非法指令（可执行文件本身错误，或部分情况下的堆栈溢出）
#define SIGABRT         6       // abort函数生成的信号
#define SIGFPE          8       // 错误且致命的算术运算（浮点运算错误, 溢出，除数为0等错误）
#define SIGSEGV         11      // 非法访问内存（访问非自己的内存或向无写权限的内存地址写数据）
#define SIGTERM         15      // 结束程序（程序自己正常退出）

// POSIX
#define SIGHUP          1       // 挂断（用户登录终端连接结束，终止前台进程或有终端输出的后台进程）
#define SIGQUIT         3       // 退出（QUIT字符，通常是Ctrl+\，进程退出时产生core文件）
#define SIGTRAP         5       // 陷阱（断点/陷阱trap指令，由debugger使用）
#define SIGKILL         9       // 立即终止程序（未知错误可用），不可捕获
#define SIGBUS          10      // 非法地址（内存地址对齐错误）
#define SIGSYS          12      // 非法系统调用
#define SIGPIPE         13      // 管道破裂（进程间通信，如写FIFO，socket时读已终止）
#define SIGALRM         14      // alarm函数生成的时钟定时信号

// POSIX（新增）
#define SIGURG          16      // 紧急数据到达socket（带外数据out-of-band）
#define SIGSTOP         17      // 停止进程的运行（未结束），不可捕获
#define SIGTSTP         18      // 停止（SUSP字符，通常是Ctrl-Z，暂时停止进程的运行）
#define SIGCONT         19      // 让停止的进程（SIGSTOP）继续运行
#define SIGCHLD         20      // 子进程结束
#define SIGTTIN         21      // 后台进程从用户终端读取数据
#define SIGTTOU         22      // 后台进程向用户终端写数据
#define SIGPOLL         23      // 可轮询事件（System V）
#define SIGXCPU         24      // 进程占用CPU时间超限（可由getrlimit/setrlimit读写该阈值）
#define SIGXFSZ         25      // 进程扩大文件大小超限
#define SIGVTALRM       26      // 虚拟时钟信号（计算进程占用CPU时间）
#define SIGPROF         27      // 虚拟时钟信号（计算进程占用CPU时间及系统调用时间）
#define SIGUSR1         30      // 用户自定义信号 1
#define SIGUSR2         31      // 用户自定义信号 2

/* kill：发送信号（对外） */
int kill(pid_t pid, int sig);
// #include <signal.h>
// pid：进程或进程组PID
//     - >0：进程
//     - 0：与当前进程同组的进程
//     - -1：所有进程表中的进程（除了最大PID进程）
//     - <-1：组号为|pid|的所有进程
// sig：SIGXXX信号
// 返回值：0（失败：-1）

/* raise：发送信号（自身） */
int raise(int sig);
// #include <signal.h>
// sig：SIGXXX信号
// 返回值：0（失败：-1）

/* alarm：定时器 */
unsigned int alarm(unsigned int sec);
// #include <unistd.h>
// sec：定时单位秒，到时发送SIGALARM信号
// 返回值：0/上个定时器剩余时间（失败：-1）
// alarm()定时器进程唯一，新的alarm()会替代旧值

/* pause：将调用进程挂起（等待捕捉信号） */
int pause(void);
// #include <unistd.h>
// 返回值：-1

/* signal：信号处理 */
sighandler_t signal (int sig, sighandler_t handler)
// #include <signal.h>
// sig：SIGXXX信号
// handler：信号处理
//     - SIG_IGN：忽略该信号
//     - SIG_DFL：系统默认方式处理信号
//     - 自定义信号处理函数指针
// 返回值：信号处理配置（失败：-1）

/* sigaction：信号处理（更健壮） */
int sigaction(int sig, const struct sigaction *act, struct sigaction *old_act);
// #include <signal.h>
// sig：SIGXXX信号（除了SIGKILL，SIGSTOP）
// act：指定对特定信号的处理
// old_act：保留原来对信号的处理
// 返回值：0（失败：-1）

/* sigaction：sigaction()信号处理 */
struct sigaction {
    sighandler_t sa_handler;       // 信号处理
    sigset_t sa_mask;              // 信号处理过程中屏蔽的附加信号集
    int sa_flags;                  // 标志位
    void (*sa_restorer) (void);    // 还原信号处理
};
// #include <bits/sigaction.h>
// sa_flags:
//     - SA_NOCLDSTOP：通过SIGSTOP终止的子进程不会在父进程产生SIGCHLD（信号为SIGCHLD时使用）
//     - SA_NOCLDWAIT — 不在子进程终止时创建僵尸进程或状态信息
//     - SA_NODEFER ― 不自动阻止信号进入处理
//     - SA_RESETHAND ― 信号处理前将处理程序重置为SIG_DFL
//     - SA_SIGINFO ― 将此信号排队

/* sig*set：信号集（非阻塞信号才起作用）函数 */
int sigemptyset(sigset_t *set);             // 将信号集初始化为空（全0）
int sigfillset(sigset_t *set);              // 将信号集初始化为包含所有已定义的信号集（全1）
int sigaddset(sigset_t *set, int signo);    // 将某信号加入到信号集中（该信号位置为1）
int sigdelset(sigset_t *set, int signo);    // 将某信号从信号集中删除（该信号位置为0）
int sigismember(sigset_t *set, int signo);  // 查询某信号是否在信号集中（该信号位置的值）
// #include <signal.h>
// set：信号集
// signo：信号代码
// 返回值：0（失败：-1）
// sigismember()函数返回值成功1，失败0
// sigset_t是64bits，对应64个信号（见信号define，实际上没有那么多），用于批量管理

/* sigprocmask：检测并更改信号屏蔽字（被阻塞的一组信号，不会被进程接受） */
int sigprocmask(int how, const sigset_t *set, sigset_t *oset);
// #include <signal.h>
// how：处理方式
//     - SIG_BLOCK：将set信号集加入信号屏蔽字
//     - SIG_UNBLOCK：从信号屏蔽字中删除set信号集
//     - SIG_SETMASK：将set设置为信号屏蔽字（覆盖）
// set：信号集，非NULL则修改信号屏蔽字
// oset：更改前的信号集，非NULL则可读取oset
// 返回值：0（失败：-1）
// 信号屏蔽（状态）字位于进程控制块（PCB）中的结构体，64bits，1屏蔽，0不屏蔽

/* sigpending：获取当前进程所有未决的信号 */
int sigpending(sigset_t *set);
// #include <signal.h>
// set：返回的未决信号集
// 返回值：0（失败：-1）
// 未决（pending），信号从产生到传递给进程前的状态

/* semget：创建/获取（已有）信号量 */
int semget(key_t key, int nsems, int semflg);
// #include <sys/sem.h>
// key：信号量键值（多个进程访问同一个信号量，私有信号量获取用IPC_PRIVATE）
// nsems：需要创建的信号量数目
// semflg：创建方式
//     - IPC_CREAT：创建信号量，若存在则获取
//     - IPC_EXCL：创建信号量，若存在则报错
// 返回值：信号量标识符（失败：-1）

/* semctl：操作信号量 */
int semctl(int semid, int semnum, int cmd, union semun arg);
// #include <sys/sem.h>
// semid：信号量标识符，操作对象
// semnum：信号量编号（信号量集有用，单个信号量/第一个为0）
// cmd：信号量操作
//     - IPC_RMID：删除semid信号量/信号量集
//     - IPC_SET：将arg.buf（struct semid_ds）数据写入信号量/信号量集
//     - IPC_STAT：获得信号量/信号量集的数据存入arg.buf（struct semid_ds）
//     - IPC_GETVAL/GETVAL：获取信号量的当前值
//     - IPC_SETVAL/SETVAL：将信号量的值设置为arg.val
// arg：union semun（该联合体可能需要自行定义）
// 返回值：0（失败：-1）
// IPC_GETVAL/GETVAL成功返回信号量的当前值

/* semun：semctl()操作的联合体 */
union semun {
    int val;                 // IPC_SETVAL/SETVAL - 信号量设置值
    struct semid_ds *buf;    // IPC_SET，IPC_STAT - 缓存区
    unsigned short *array;   // GETALL，SETALL - 数组
    struct seminfo *__buf;   // IPC_INFO - 缓存区（GNU Linux）
};
// 不是GNU Linux，可以忽略__buf

/* semid_ds：信号量集合 */
struct semid_ds {
    struct ipc_perm sem_perm;   // 所有者和权限
    time_t sem_otime;           // 上次semop()的时间
    time_t sem_ctime;           // 上次更新的时间
    unsigned short sem_nsems;   // 在信号量集合里的索引号
 };
// #include <bits/sem.h>

/* ipc_perm：IPC操作权限描述 */
struct ipc_perm {
    key_t __key;             // 键值（信号量，共享内存，消息队列等IPC）
    uid_t uid;               // 所有者UID
    gid_t gid;               // 所有者GID
    uid_t cuid;              // 创建者UID
    gid_t cgid;              // 创建者GID
    unsigned short mode;     // 读/写权限
    unsigned short __seq;    // 序列号
};
// #include <bits/ipc.h>

/* semop：信号量PV操作 */
int semop(int semid, struct sembuf *sops, size_t nsops);
// #include <sys/sem.h>
// semid：信号量标识符，操作对象
// sops：（struct sembuf）信号量操作数组
// nsops：sops信号量操作数组的元素数目（通常为1）
// 返回值：信号量标识符（失败：-1）

/* sembuf：semop()操作的结构体 */
struct sembuf {
  unsigned short sem_num;   // 信号量编号
  short sem_op;             // 信号量操作
  short sem_flg;            // 操作标识
};
// #include <sys/sem.h>
// sem_op：一般为+1/-1
//     - <0：P操作（信号量-|sem_op|）
//         - semval-|sem_op| >= 0时，semval-|sem_op|并为该线程分配对应数目的资源（sem_flag=SEM_UNDO时，semadj+|sem_op|）
//         - semval-|sem_op| < 0时，semncnt+1（调用线程被阻塞），直到semval >= |sem_op|时，semncnt-1（调用线程被唤醒）
//     - >0：V操作（信号量+sem_op，em_flag=SEM_UNDO时，semadj-sem_op）
//         - semval+sem_op > 0时，继续阻塞
//         - semval+sem_op <= 0时，唤醒一个进程（P操作阻塞的进程队列）
//     - 0：semval为0则立即返回；不为0则semzcnt+1
// sem_flg：
//     - 0：正常操作
//     - SEM_UNDO（建议）：维护进程对信号量的调整值（进程结束时，操作系统根据semadj值恢复信号量）
//     - IPC_WAIT：使信号量操作是非阻塞的（不满足条件的情况下不会被阻塞，而是直接返回-1，并且errno=EAGAIN）
// semval：信号量当前值
// semncnt：等待semval变为>当前值的线程数
// semzcnt：等待semval变为=0的线程数
// semadj：信号量对某个特定进程的调整值（sem_flag=SEM_UNDO时，semadj随sem_op更新）

/* sem_init：创建并初始化信号量 */
int sem_init(sem_t *sem, int pshared, unsigned int value);
// #include <semaphore.h>
// sem：信号量指针
// pshared：信号量能在几个进程间共享（0即当前进程）
// value：信号量初始化值
// 返回值：0（失败：-1）

/* sem_wait：P操作（>=0时信号量-1，<0时阻塞进程） */
int sem_wait(sem_t *sem);
// #include <semaphore.h>
// sem：信号量指针
// 返回值：0（失败：-1）

/* sem_trywait：P操作（>=0时信号量-1，<0时立即返回） */
int sem_trywait(sem_t *sem);
// #include <semaphore.h>
// sem：信号量指针
// 返回值：0（失败：-1）

/* sem_post：V操作（信号量+1，唤醒阻塞的进程） */
int sem_post(sem_t *sem);
// #include <semaphore.h>
// sem：信号量指针
// 返回值：0（失败：-1）

/* sem_getvalue：得到信号量的值 */
int sem_getvalue(sem_t *sem);
// #include <semaphore.h>
// sem：信号量指针
// 返回值：信号量的值（失败：-1）

/* sem_destroy：删除信号量 */
int sem_destroy(sem_t *sem);
// #include <semaphore.h>
// sem：信号量指针
// 返回值：0（失败：-1）

/* shmget：创建/获取共享内存段 */
int shmget(key_t key, size_t size, int shmflg);
// #include <sys/shm.h>
// key：共享内存键值（多个进程访问同一个共享内存，私有共享内存获取用IPC_PRIVATE）
// size：共享内存段大小
// shmflg：权限标识
// 返回值：共享内存段标识符（失败：-1）

/* shmat：映射共享内存段 */
void *shmat(int shmid, const void *shmaddr, int shmflg);
// #include <sys/shm.h>
// shmid：要映射的共享内存段标识符
// shmaddr：将共享内存映射到指定地址（0：系统自动分配地址并将该段共享内存映射到调用进程的地址空间）
// shmflg：共享内存读写权限
//     - SHM_RDONLY：只读
//     - 0（默认）：可读写
// 返回值：被映射的共享内存段地址（失败：-1）

/* shmdt：撤销已映射的共享内存段 */
int shmdt(const void *shmaddr);
// #include <sys/shm.h>
// shmaddr：被映射的共享内存段地址
// 返回值：0（失败：-1）

/* msgget：创建/打开消息队列 */
int msgget(key_t key, int msgflg);
// #include <sys/msg.h>
// key：消息队列键值（多个进程访问同一个消息队列，私有消息队列获取用IPC_PRIVATE）
// msgflg：权限标识
// 返回值：消息队列标识符/ID（失败：-1）

/* msgrcv：接收消息 */
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long int msgtyp, int msgflg);
// #include <sys/msg.h>
// msqid：消息队列标识符
// msgp：消息缓冲
// msgsz：消息正文的字节数（不包括消息类型指针变量）
// msgtyp：消息类型
//     - 0：接收消息队列中第一个消息
//     - >0：接收消息队列中第一个类型为msgtyp的消息
//     - <0：接收消息队列中第一个类型为<=|msgtyp|的消息
// msgflg：
//     - 0：将msgsnd()调用阻塞，直到接收到一条相应类型（msgtyp）的消息
//     - MSG_NOERROR：若返回消息字节数>=msgsz则截断，且不通知消息发送进程
//     - IPC_NOWAIT：若消息队列没有相应类型可以接收则立即返回
// 返回值：0（失败：-1）

/* msgbuf：消息缓冲 */
struct msgbuf {
  long mtype;       // 发送/接收消息的类型
  char mtext[1];    // 消息正文
};
// #include <sys/msg.h>

/* msgsnd：发送消息 */
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
// #include <sys/msg.h>
// msqid：消息队列标识符
// msgp：消息缓冲
// msgsz：消息正文的字节数
// msgflg：
//     - 0：msgsnd()调用阻塞，直到发送成功
//     - IPC_NOWAIT：若消息无法立即发送（消息队列已满）则立即返回
// 返回值：信号量标识符（失败：-1）

/* msgctl：控制消息队列 */
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
// #include <sys/msg.h>
// msqid：消息队列标识符
// cmd：命令参数
//     - IPC_STAT：读取消息队列的数据，并将其存放在buf
//     - IPC_SET：用buf->ipc_perm的值设置消息队列相应的值
//     - IPC_RMID：从内核中删除消息队列
// buf：消息队列描述结构体（struct msqid_ds）
// 返回值：信号量标识符（失败：-1）

/* msqid_ds：消息队列描述结构体 */
struct msqid_ds {
    struct ipc_perm msg_perm;     // 所有者和权限
    time_t          msg_stime;    // 上次msgsnd()的时间
    time_t          msg_rtime;    // 上次msgrcv()的时间
    time_t          msg_ctime;    // 上次更新的时间
    unsigned long   __msg_cbytes; // 队列中的当前字节数（不标准）
    msgqnum_t       msg_qnum;     // 队列中的当前消息数
    msglen_t        msg_qbytes;   // 队列中允许的最大字节数
    pid_t           msg_lspid;    // 上次msgsnd()的PID
    pid_t           msg_lrpid;    // 上次msgrcv()的PID
};
// #include <bits/msq.h>


/* ————————————————————————————————————————————————————————————————————————————————————————————————————
 * socket
 * ——————————————————————————————————————————————————————————————————————————————————————————————————— */

/* socket：创建socket描述符并唯一标识 */
int socket(int domain, int type, int protocol);
// #include <sys/socket.h>
// domain：协议族（AF：Address Family；PF：Protocol Family）
//     - AF_INET：IPv4
//     - AF_INET6：IPv6
//     - AF_LOCAL/AF_UNIX：Unix
// type：套接字类型，即数据传输方式
//     - SOCK_STREAM：流
//     - SOCK_DGRAM：数据报
// protocol：传输协议
//     - 0：根据domain和type自动选择protocol
//     - IPPROTO_TCP：TCP协议
//     - IPPTOTO_UDP：UDP协议
// 返回值：socket描述符（也是文件描述符）

/* bind：绑定socket与协议地址（IP + 端口号） */
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// #include <sys/socket.h>
// sockfd：待绑定的socket描述符
// addr：指向绑定给sockfd的协议地址
//     - sockaddr_in：AF_INET
//     - sockaddr_in6：AF_INET6
//     - sockaddr_un：AF_LOCAL/AF_UNIX
// addrlen：addr地址的长度
// 返回值：0（失败：-1）

/* listen：服务端，监听socket */
int listen(int sockfd, int backlog);
// #include <sys/socket.h>
// sockfd：待监听的socket描述符（作为服务端）
// backlog：相应socket可以排队的最大连接个数
// 返回值：0（失败：-1）

/* connect：客户端，连接socket */
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// #include <sys/socket.h>
// sockfd：待连接的socket描述符（作为客户端）
// addr：服务端的sockfd的协议地址
// addrlen：addr地址的长度
// 返回值：0（失败：-1）

/* accept：服务端，接收socket的连接（connect），并返回用于通信的socket描述符 */
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
// #include <sys/socket.h>
// sockfd：待接收连接的socket描述符（作为服务端）
// addr：客户端的sockfd的协议地址
// addrlen：addr地址的长度
// 返回值：socket描述符（失败：-1）

/* send：TCP发送数据 */
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
// #include <sys/socket.h>
// sockfd：socket描述符（作为服务器时，为accept返回）
// buf：缓冲区（发送数据）
// len：长度（发送数据）
// flags：信息模式（默认0：阻塞式）
// 返回值：发送的数据大小（=0，超时/close；<0，失败/errno为EINTR|EWOULDBLOCK|EAGAIN时连接正常）

/* recv：TCP接收数据 */
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
// #include <sys/socket.h>
// sockfd：socket描述符（作为服务器时，为accept返回）
// buf：缓冲区（接收数据）
// len：长度（接收数据）
// flags：信息模式（默认0：阻塞式）
// 返回值：接收到的数据大小（=0，超时/close；<0，失败/errno为EINTR|EWOULDBLOCK|EAGAIN时连接正常）

/* sendto：UDP发送数据 */
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
// #include <sys/socket.h>
// sockfd：socket描述符（作为服务器时，为accept返回）
// buf：缓冲区（发送数据）
// len：缓冲区长度（发送数据）
// flags：信息模式（默认0：阻塞式）
// dest_addr：发送的目的sockfd的协议地址
// addrlen：长度（dest_addr）
// 返回值：发送的数据大小（失败：-1）

/* recvto：UDP接收数据 */
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
// #include <sys/socket.h>
// sockfd：socket描述符（作为服务器时，为accept返回）
// buf：缓冲区（接收数据）
// len：缓冲区长度（接收数据）
// flags：信息模式（默认0：阻塞式）
// src_addr：接受的源sockfd的协议地址
// addrlen：长度（src_addr）
// 返回值：接收到的数据大小（失败：-1）

/* sendmsg：发送数据 */
ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
// #include <sys/socket.h>
// sockfd：socket描述符（作为服务器时，为accept返回）
// msg：信息
// flags：信息模式（默认0：阻塞式）
// 返回值：发送的数据大小（失败：-1）

/* recvmsg：接收数据 */
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
// #include <sys/socket.h>
// sockfd：socket描述符（作为服务器时，为accept返回）
// msg：信息
// flags：信息模式（默认0：阻塞式）
// 返回值：接收到的数据大小（失败：-1）

/* msghdr：缓冲区结构体 */
struct iovec {
    void    *iov_base;   // 缓冲区首地址
    size_t   iov_len;    // 缓冲区长度
};
#include <sys/uio.h>

/* msghdr：传输信息结构体 */
struct msghdr {
    void         *msg_name;        // UDP中发送/接受方的协议地址（TCP无需指定，为NULL）
    socklen_t     msg_namelen;     // 长度（msg_name）
    struct iovec *msg_iov;         // 缓冲区
    size_t        msg_iovlen;      // 缓冲区长度（msg_iov）
    void         *msg_control;     // 辅助数据
    size_t        msg_controllen;  // 辅助数据长度（msg_control）
    int           msg_flags;       // 信息模式（sendmsg忽略）
};
#include <sys/socket.h>
