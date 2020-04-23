/** 
 * notifier.c：接收处理通知链事件
 */
#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/init.h>
 
#include <linux/kernel.h>	/* printk() */
#include <linux/fs.h>	/* everything() */
 
extern int register_event_notifier(struct notifier_block *nb);
#define TESTCHAIN_INIT 0x52U
 
/* realize the notifier_call func */
int deal_with_event_notifier(struct notifier_block *nb, unsigned long event,
	void *v)
{
	switch(event){
	case TESTCHAIN_INIT:
		printk(KERN_DEBUG "I got the chain event, message: %s\n", (char *)v);
		break;
 
	default:
		break;
	}
 
	return NOTIFY_DONE;
}
/* define a notifier_block */
static struct notifier_block event_notifier_init = {
	.notifier_call = deal_with_event_notifier,
};
static int __init notifier_chain_init(void)
{
	printk(KERN_DEBUG "I'm in notifier_chain_init\n");
	register_event_notifier(&event_notifier_init);	// 由notifier提供的设施
	return 0;
}
 
static void __exit notifier_chain_exit(void)
{
	printk(KERN_DEBUG "Goodbye to notifier_chain_exit\n");
}
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("fishOnFly");
 
module_init(notifier_chain_init);
module_exit(notifier_chain_exit);
