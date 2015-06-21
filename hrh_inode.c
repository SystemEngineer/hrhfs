#include <linux/fs.h>
#include "hrh_fs.h"

const struct inode_operations hrhfs3_dir_inode_operations = {
    .create     = hrhfs_create,
    .lookup     = hrhfs_lookup,
    .link       = hrhfs_link,
    .unlink     = hrhfs_unlink,
    .symlink    = hrhfs_symlink,
    .mkdir      = hrhfs_mkdir,
    .rmdir      = hrhfs_rmdir,
    .mknod      = hrhfs_mknod,
    .rename     = hrhfs_rename,
    .permission = hrhfs_permission,
    .getattr    = hrhfs_getattr,
    .setattr    = hrhfs_setattr,
    .listxattr  = hrhfs3_listxattr,
    .getxattr   = hrhfs3_getxattr,
    .setxattr   = hrhfs3_setxattr,
    .removexattr    = hrhfs3_removexattr,
};