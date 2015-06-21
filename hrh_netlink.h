#ifndef __HRH_NETLINK_H__
#define __HRH_NETLINK_H__

#include <net/sock.h>
#include <linux/netlink.h>


#define MAX_MSG_SIZE 4096
#define HRH_NETLINK_PID  9527
#define HRH_NETLINK_TYPE 25 //GENERIC NETLINK

int send_by_netlink(struct sock *nlfd, char* msg, int msg_size);
int create_netlink(struct sock **nlfd,struct module *mod);

#endif