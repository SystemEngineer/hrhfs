#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include "hrh_fs.h"
#include "hrh_netlink.h"

static struct sock *netlinkfd = NULL;

static int hrhfs_fill_super(struct super_block *sb, void *data, int silent)  
{  
    static struct tree_descr hrhfs_files[] = {{""}};  
    dprintk("Filling super block of hrhfs......\n");
    return simple_fill_super(sb, 0x64669527, hrhfs_files);  
} 

static struct dentry *hrhfs_fs_mount(struct file_system_type *fs_type,
    int flags, const char *dev_name, void *raw_data){
    dprintk("Mounting hrhfs, dev_name is %s......\n", dev_name);
    send_by_netlink(netlinkfd, "Hello World", 12);
    return mount_single(fs_type, flags, raw_data, hrhfs_fill_super);
}

static void hrhfs_kill_super(struct super_block *s){
    kill_anon_super(s);
}

static struct file_system_type hrhfs_fs_type = {
    .owner      = THIS_MODULE,
    .name       = "hrhfs",
    .mount      = hrhfs_fs_mount,
    .kill_sb    = hrhfs_kill_super,
};

static int __init init_hrh_fs(void){
    int ret;

    dprintk("Loading hrhfs......\n");
    ret = create_netlink(&netlinkfd, THIS_MODULE);
    if(ret != 0){
        return -ENOMEM;
    }
    register_filesystem(&hrhfs_fs_type);
    dprintk("Loading hrhfs......Done\n");
    return 0;
}

static void __exit exit_hrh_fs(void){
    dprintk("Unloading hrhfs......\n");
    unregister_filesystem(&hrhfs_fs_type);
    sock_release(netlinkfd->sk_socket);
    dprintk("Unloading hrhfs......Done\n");
}

module_init(init_hrh_fs);
module_exit(exit_hrh_fs);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("H.RH<heronghui@gmail.com>");
MODULE_DESCRIPTION("H.RH VFS practice");