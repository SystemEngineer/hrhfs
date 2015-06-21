#ifndef __HRH_FS_H__
#define __HRH_FS_H__

#define HRHFS_DEBUG 1

#if HRHFS_DEBUG
#define dprintk(format, a...)                       \
    do {                                \
        printk(KERN_INFO "[hrhfs]" format, ##a);         \
    } while (0)
#else
#define dprintk(format...)
#endif


#endif