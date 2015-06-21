KERNEL_PATH := /lib/modules/`uname -r`/build
CURRENT_PATH := `pwd`
obj-m = hrhfs.o 
hrhfs-objs = hrh_fs.o hrh_netlink.o

all: 
	make -C $(KERNEL_PATH) M=$(CURRENT_PATH) modules 
clean: 
	make -C $(KERNEL_PATH) M=$(CURRENT_PATH) clean
