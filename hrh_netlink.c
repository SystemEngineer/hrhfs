#include "hrh_fs.h"
#include "hrh_netlink.h"

int send_by_netlink(struct sock *nlfd, char* msg, int msg_size){
    int size;
    struct sk_buff *skb;
    sk_buff_data_t old_tail;
    struct nlmsghdr *nlhdr;
    int ret;

    size = NLMSG_SPACE(msg_size);
    skb = alloc_skb(size, GFP_ATOMIC);

    nlhdr = nlmsg_put(skb, 0, 0, 0, size - sizeof(struct nlmsghdr), 0);
    old_tail = skb->tail;
    memcpy(NLMSG_DATA(nlhdr), msg, msg_size);
    nlhdr->nlmsg_len = skb->tail - old_tail;

    NETLINK_CB(skb).pid = 0;
    NETLINK_CB(skb).dst_group = 0;  //dst_group is used for broadcast

    ret = netlink_unicast(nlfd, skb, HRH_NETLINK_PID, MSG_DONTWAIT);
    //ret = netlink_broadcast(nlfd, skb, 0, 1, GFP_KERNEL);
    dprintk("Send message to userspace, return with %d\n", ret);

    return 0;
}

void recv_by_netlink(struct sk_buff *sk){
    dprintk("Receive a message from userspace.\n"); 
}

int create_netlink(struct sock **nlfd, struct module *mod){
    //Attention: The userspace worker must start after this creation.
    *nlfd = netlink_kernel_create(&init_net, HRH_NETLINK_TYPE, 0, recv_by_netlink, NULL, mod);
    if (!(*nlfd)) {
        dprintk("Fail to create netlink socket.\n");
        return -1;
    }
    return 0;
}