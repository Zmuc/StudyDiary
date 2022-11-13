/* 内核cmdline参数读取 */
__setup("xxx=", xxx_setup);
// "xxx="：内核cmdline参数选项
// xxx_setup：内核cmdline参数处理函数，其函数参数为内核cmdline参数值
// xxx=1 -> xxx_setup(1)

/* 定义LSM模块 - xxx */
DEFINE_LSM(xxx) = {
    .name = "xxx",
    .flags = LSM_FLAG_LEGACY_MAJOR | LSM_FLAG_EXCLUSIVE,
    .enabled = &xxx_enabled_boot,
    .blobs = &xxx_blob_sizes,
    .init = xxx_init,
};
// DEFINE_LSM宏定义lsm_info结构体
// .name/.flags/.enabled/.blobs/.init是lsm_info结构体成员
// .name成员（const char *name;）必需，是LSM模块名
// .init成员（int (*init)(void);）必需，是LSM模块xxx的初始化函数指针

/* 文件操作 */
struct file_operations {
    // ...
    ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
    ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
    int (*mmap) (struct file *, struct vm_area_struct *);
    int (*open) (struct inode *, struct file *);
    int (*flush) (struct file *, fl_owner_t id);
    int (*release) (struct inode *, struct file *);
    int (*lock) (struct file *, int, struct file_lock *);
    // ...
};
static const struct file_operations xxx_load_ops = {
    .write          = xxx_write_load,
    .llseek         = generic_file_llseek,
};
// 存储驱动内核模块提供的对设备进行各种操作的函数指针（成员都是函数指针）
// xxx_load_ops实现某类设备的操作（write和llseek），而其他成员为NULL（NULL意味着该类设备不需要该操作）
// struct file代表一个设备文件（仅内核空间代码）

/* 索引节点操作 */
struct inode_operations {
    // ...
    int (*permission) (struct inode *, int);
    int (*create) (struct inode *,struct dentry *, umode_t, bool);
    int (*link) (struct dentry *,struct inode *,struct dentry *);
    int (*symlink) (struct inode *,struct dentry *,const char *);
    int (*mkdir) (struct inode *,struct dentry *,umode_t);
    int (*rmdir) (struct inode *,struct dentry *);
    int (*rename) (struct inode *, struct dentry *,
                   struct inode *, struct dentry *, unsigned int);
    int (*setattr) (struct dentry *, struct iattr *);
    int (*getattr) (const struct path *, struct kstat *, u32, unsigned int);
    int (*fiemap)(struct inode *, struct fiemap_extent_info *, u64 start, u64 len);
    // ...
};
// struct inode_operations对索引节点和文件系统都适用
// 未实现成员为NULL

/* 定义init调用 */
#define __define_initcall(fn, level)
#define rootfs_initcall(fn)             __define_initcall(fn, rootfs)
// fn：init函数
// level：优先级（level小优先，不含s优先），5s < rootfs < 6
// initcall_t类型(函数指针)的变量，在.initcall#id.init的subsection中

/* 使用init调用 */
__initcall(xxx_todo);
#define __initcall(fn) device_initcall(fn)
#define device_initcall(fn)             __define_initcall(fn, 6)
// __initcall == device_initcall == __define_initcall(fn, 6)
// __initcall：一般服务常用的init优先级，为6
// xxx_todo：init函数

/* 内核CONFIG使用 */
// Kconfig，内核CONFIG信息介绍
config XXX_1
// *defconfig，内核CONFIG配置
CONFIG_XXX_1
// *.c/h，内核CONFIG宏判断（是否定义/内容）
#ifdef CONFIG_XXX_1
    // enable to do
#else
    // disable to do
#endif

/* 缓存 */
struct kmem_cache *xxx_node_cachep;
xxx_node_cachep = kmem_cache_create("xxx_node", sizeof(struct xxx_node), 0, SLAB_PANIC, NULL);
// struct kmem_cache：高速缓存接口，来自cache_cache结构体
// kmem_cache_create：创建缓存（kmem_cache）
// AVC（访问向量缓存）也是使用的kmem_cache


/* ------  哈希链表  ------ */
/*
--------------
|            |        hlist_node
--------------        --------------
| hlist_head |  -->   | next       |  ...
--------------        --------------
|            |        | pprev      |
--------------        --------------
*/
struct hlist_head {
        struct hlist_node *first;
};
// first指向链表第一个hlist_node
struct hlist_node {
    struct hlist_node *next, **pprev;
};
// pprev指向上一个hlist_node的next指针

// 哈希链表头和结点初始化
#define HLIST_HEAD_INIT { .first = NULL }
#define HLIST_HEAD(name) struct hlist_head name = { .first = NULL }
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
static inline void INIT_HLIST_NODE(struct hlist_node *h) {
        h->next = NULL;
        h->pprev = NULL;
};

// 哈希链表判空
static inline int hlist_empty(const struct hlist_head *h) {
        return !READ_ONCE(h->first);
};
// 通过hlist_head中first判断是否为NULL

// 判断结点是否在哈希链表上
static inline int hlist_unhashed(const struct hlist_node *h) {
        return !h->pprev;
};
// 通过hlist_node中pprev判断是否在哈希链表上（pprev指向上一结点的next指针，为NULL则不在哈希链表中）

// 哈希链表增加结点
static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h);
static inline void hlist_add_before(struct hlist_node *n, struct hlist_node *next) {
        WRITE_ONCE(n->pprev, next->pprev);
        WRITE_ONCE(n->next, next);
        WRITE_ONCE(next->pprev, &n->next);
        WRITE_ONCE(*(n->pprev), n);
};
static inline void hlist_add_behind(struct hlist_node *n, struct hlist_node *prev);
// 依次：加在开头|加在之前|加在之后
// 举例：hlist_add_before，将形参next改为n1便于理解，且其上一结点为n0
//      1.将n1的pprev赋值给n的pprev，即新增结点n的pprev指向n0的next
//      2.将n1赋值给n的next，即新增结点n的next指向n1结点
//      1-2：处理新增结点n的指向，即n0 --> n --> n1（n角度）
//      3.将n1的pprev指向n的next地址，即新增结点n的next被n1的pprev指向
//      4.将n上一个结点的next指向n，即新增结点被n0的next指向
//      3-4：处理新增结点n的被指向，即n0 --> n --> n1（n0，n1角度）

// 哈希链表删除结点
static inline void hlist_del(struct hlist_node *n);
static inline void hlist_del_init(struct hlist_node *n);
// 依次：结点删除后不可用|结点删除后为NULL

// 哈希链表遍历
#define hlist_entry(ptr, type, member) container_of(ptr,type,member)
// 通过hlist_head获取所有结点数据
// ptr：哈希链表地址
// type：哈希链表类型
// member：哈希链表中hlist_head成员的变量名

#define hlist_for_each(pos, head) \
        for (pos = (head)->first; pos ; pos = pos->next)
// pos从第一个哈希结点开始，直到为NULL（即遍历到最后）
// pos：辅助指针（hlist_node），用于链表遍历
// head：链表头指针（hlist_head）

#define hlist_for_each_safe(pos, n, head) \
        for (pos = (head)->first; pos && ({ n = pos->next; 1; }); \
             pos = n)
// 原理与hlist_for_each一致，n用来避免因遍历过程中删除pos指向节点导致的断链问题
// pos：辅助指针（hlist_node），用于链表遍历
// n：链表结点指针（hlist_node），临时存储pos的下一个链表结点
// head：链表头指针（hlist_head）

#define hlist_entry_safe(ptr, type, member) \
        ({ typeof(ptr) ____ptr = (ptr); \
           ____ptr ? hlist_entry(____ptr, type, member) : NULL; \
        })
// 更安全的hlist_entry

#define hlist_for_each_entry(pos, head, member)                         \
        for (pos = hlist_entry_safe((head)->first, typeof(*(pos)), member);\
             pos;                                                       \
             pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))
// 开始遍历位置：哈希链表的第一个哈希结点

#define hlist_for_each_entry_continue(pos, member)                      \
        for (pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member);\
             pos;                                                       \
             pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))
// 开始遍历位置：哈希链表的pos结点的下一个结点

#define hlist_for_each_entry_from(pos, member)                          \
        for (; pos;                                                     \
             pos = hlist_entry_safe((pos)->member.next, typeof(*(pos)), member))
// 开始遍历位置：哈希链表的pos结点的当前结点

current_cred

/* ------  预测条件分支  ------ */
#define likely_notrace(x)    __builtin_expect(!!(x), 1)
#define unlikely_notrace(x)  __builtin_expect(!!(x), 1)
#define likely(x)     (__branch_check__(x, 1, __builtin_constant_p(x)))
#define unlikely(x)   (__branch_check__(x, 0, __builtin_constant_p(x)))
// likely*，x==1发生概率大，即if{}语句编译在前面
// unlikely*，x==0发生概率大。即else{}语句编译在前面
// 原来的likely/unlikely定义为likely_notrace/unlikely_notrace


/* ------  通过局部计算整体的首地址  ------ */
#define container_of(ptr, type, member) ({                              \
        void *__mptr = (void *)(ptr);                                   \
        BUILD_BUG_ON_MSG(!__same_type(*(ptr), ((type *)0)->member) &&   \
                         !__same_type(*(ptr), void),                    \
                         "pointer type mismatch in container_of()");    \
        ((type *)(__mptr - offsetof(type, member))); })
// 由[结构体中变量某成员地址 + 该成员名字 + 该结构体类型]，求解该结构体的首地址
// ptr：结构体变量中某个成员的地址
// type：结构体类型
// member：该结构体变量的名字
