#include "hrh_fs.h"

const struct file_operations hrhfs_file_operations = {
    .llseek     = hrhfs_file_llseek,
    .read       = do_sync_read,
    .write      = do_sync_write,
    .aio_read   = hrhfs_file_read,
    .aio_write  = hrhfs_file_write,
    .mmap       = hrhfs_file_mmap,
    .open       = hrhfs_file_open,
    .flush      = hrhfs_file_flush,
    .release    = hrhfs_file_release,
    .fsync      = hrhfs_file_fsync,
    .lock       = hrhfs_lock,
    .flock      = hrhfs_flock,
    .splice_read    = hrhfs_file_splice_read,
    .splice_write   = hrhfs_file_splice_write,
    .check_flags    = hrhfs_check_flags,
    .setlease   = hrhfs_setlease,
};