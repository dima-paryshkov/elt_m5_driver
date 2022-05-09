#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include <net/net_namespace.h>

#define NETLINK_USER 31
#define MSG_SIZE 512

struct sock *nl_sk = NULL;

static void hello_nl_recv_msg(struct sk_buff *skb)
{
    char msg[MSG_SIZE];
    struct nlmsghdr *nlh;
    int pid;
    struct sk_buff *skb_out;
    int res;

    static int count = 0;

    count++;

    printk(KERN_INFO "Entering: %s\n", __FUNCTION__);


    nlh = (struct nlmsghdr *)skb->data;
    printk(KERN_INFO "Netlink received msg payload: %s\n", (char *)nlmsg_data(nlh));
    pid = nlh->nlmsg_pid; 

    snprintf(msg, MSG_SIZE, "%s%d.\n%s%s", "Hello from kernel. Request number: ", count, "Echo: ", (char *)nlmsg_data(nlh));

    skb_out = nlmsg_new(MSG_SIZE, 0);

    if (!skb_out)
    {
        printk(KERN_ERR "Failed to allocate new skb\n");
        return;
    }
    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, MSG_SIZE, 0);
    NETLINK_CB(skb_out).dst_group = 0; 
    strncpy(nlmsg_data(nlh), msg, MSG_SIZE);

    res = nlmsg_unicast(nl_sk, skb_out, pid);

    if (res < 0)
        printk(KERN_INFO "Error while sending bak to user\n");
}

struct netlink_kernel_cfg cfg = {
    .groups = 1,
    .input = hello_nl_recv_msg,
};

static int __init hello_init(void)
{
    printk("Entering: %s\n", __FUNCTION__);
    nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);

    if (!nl_sk)
    {
        printk(KERN_ALERT "Error creating socket.\n");
        return -10;
    }

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "exiting hello module\n");
    netlink_kernel_release(nl_sk);
}
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");