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
