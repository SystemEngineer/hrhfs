#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/netlink.h>

#define MAX_MSG_SIZE 4096
#define HRH_NETLINK_PID  9527
#define HRH_NETLINK_TYPE 25     //GENERIC NETLINK

int main(){
    struct sockaddr_nl src_addr, dst_addr;
    struct nlmsghdr *nlhdr = NULL;
    struct msghdr msg;
    struct iovec iov;
    int sd;
    int ret = 1;

    //Attention: The kernel module with HRH_NETLINK_TYPE must be loaded before this program!
    sd = socket(AF_NETLINK, SOCK_RAW, HRH_NETLINK_TYPE);
    perror("Create socket:");
    memset(&src_addr, 0, sizeof(src_addr));
    memset(&dst_addr, 0, sizeof(dst_addr));

    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = HRH_NETLINK_PID;  //Attention: can be pid, but not must be
    src_addr.nl_groups = 1;
    bind(sd, (struct sockaddr *)&src_addr, sizeof(src_addr));

    nlhdr = (struct nlmsghdr*)malloc(NLMSG_SPACE(MAX_MSG_SIZE));

    printf("Waiting for message from kernel......\n");

    while(1){
        memset(nlhdr, 0, NLMSG_SPACE(MAX_MSG_SIZE));
        iov.iov_base = (void *)nlhdr;
        iov.iov_len = NLMSG_SPACE(MAX_MSG_SIZE);
        msg.msg_name = (void *)&dst_addr;
        msg.msg_namelen = sizeof(dst_addr);
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;

        ret = recvmsg(sd, &msg, 0);
        if(ret == 0){
            printf("Empty msg, exit. \n");
            exit(0);
        }else if(ret == -1){
            perror("Recvmsg error:");
            exit(1);
        }
        //Attention: why \n is nessary??
        printf("%s\n", NLMSG_DATA(nlhdr));
    }
    close(sd);
}