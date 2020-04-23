/**
 * chain.c ：
 *   1. 定义回调函数；
 *   2. 定义notifier_block；
 *   3. 向chain_0注册notifier_block；
 */
#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/fs.h>	/* everything() */
 
#define TESTCHAIN_INIT 0x52U
static RAW_NOTIFIER_HEAD(event_chain);
 
/* define our own notifier_call_chain */
static int call_event_notifiers(unsigned long val, void *v)
{
	return raw_notifier_call_chain(&event_chain, val, v);
}
EXPORT_SYMBOL(call_event_notifiers);
 
/* define our own notifier_chain_register func */
 static int register_event_notifier(struct notifier_block *nb)
{
	int err;
	err = raw_notifier_chain_register(&event_chain, nb);
 
	if(err)
		goto out;
 
out:
	return err;
}
 
EXPORT_SYMBOL(register_event_notifier);
 
static int __init event_notifier_chain_init(void)
{
	printk(KERN_DEBUG "I'm in event_notifier_chain_init\n");
 
	return 0;
}
 
static void __exit event_notifier_chain_exit(void)
{
	printk(KERN_DEBUG "Goodbye to event_notifier_chain_exit\n");
//	call_test_notifiers(TESTCHAIN_EXIT, (int *)NULL);
}
 
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("fishOnFly");
 
module_init(event_notifier_chain_init);
module_exit(event_notifier_chain_exit);
