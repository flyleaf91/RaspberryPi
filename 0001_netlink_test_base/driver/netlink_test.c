#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/init.h>
#include <linux/ip.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/netlink.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Koorey King");

#define NETLINK_TEST    30
#define MSG_LEN         125
#define USER_PORT       100

// 全局的socket指针，用于保存NETLINK_TEST socket指针，当需要发送消息给用户空间的时候需要用到这个指针
struct sock *nlsk = NULL;

int send_usrmsg(char *pbuf, uint16_t len)
{
    struct sk_buff *nlskb;
    struct nlmsghdr *nlh;
 
    int ret;
 
    /* 创建sk_buff 空间，socket通信都是基于struct sk_buff进行通信 */
    nlskb = nlmsg_new(len, GFP_ATOMIC);
    if(!nlskb)
    {
        printk("netlink alloc failure\n");
        return -1;
    }
 
    /* 设置netlink消息头部，填充nlmsghdr结构体 */
    nlh = nlmsg_put(nlskb, 0, 0, NETLINK_TEST, len, 0);
    if(nlh == NULL)
    {
        printk("nlmsg_put failaure \n");
        nlmsg_free(nlskb);
        return -1;
    }
 
    /* 拷贝数据发送 */
    memcpy(nlmsg_data(nlh), pbuf, len);
    // 注意这里用户空间自己定义的port
    ret = netlink_unicast(nlsk, nlskb, USER_PORT, MSG_DONTWAIT);
 
    return ret;
}
 
// 当用户空间发送struct sk_buff过来的时候，会自动触发这个函数，如下是基本拆解包过程
static void netlink_rcv_msg(struct sk_buff *skb)
{
    struct nlmsghdr *nlh = NULL;
    char *umsg = NULL;
    char *kmsg = "hello users!!!";
 
    if(skb->len >= nlmsg_total_size(0))
    {
        nlh = nlmsg_hdr(skb);
        umsg = NLMSG_DATA(nlh);
        if(umsg)
        {
            printk("kernel recv from user: %s\n", umsg);
            send_usrmsg(kmsg, strlen(kmsg));
        }
    }
}



struct netlink_kernel_cfg cfg = { 
    .input  = netlink_rcv_msg, /* set recv callback */
}; 

static int __init myinit_module(void)
{
    printk("my netlink in\n");
    // net: net指向所在的网络命名空间, 一般默认传入的是&init_net(不需要定义);  定义在net_namespace.c(extern struct net init_net);
    nlsk = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);
    return 0;
}

static void __exit mycleanup_module(void)
{
    printk("my netlink out!\n");
    sock_release(nlsk->sk_socket);
}

module_init(myinit_module);
module_exit(mycleanup_module);
