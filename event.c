#include <linux/notifier.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/fs.h>	/* everything() */
 
extern int call_event_notifiers(unsigned long val, void *v);

#define TESTCHAIN_INIT 0x52U
 
static int __init send_event_chain_init(void)
{
	printk(KERN_DEBUG "I'm in send_event_chain_init\n");
	call_event_notifiers(TESTCHAIN_INIT, "no_use");
	
	return 0;
}
 
static void __exit send_event_chain_exit(void)
{
	printk(KERN_DEBUG "Goodbye to send_event_chain_exit\n");
}
 
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("fishOnFly");
 
module_init(send_event_chain_init);
module_exit(send_event_chain_exit);
