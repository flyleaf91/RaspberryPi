#include <linux/module.h>
#include <linux/init.h>
 
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/completion.h>
 
MODULE_LICENSE("GPL");
 
static int complete_major = 255;
DECLARE_COMPLETION(comp);
 
ssize_t complete_read(struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
	printk(KERN_ERR "process %i (%s) going to sleep\n", current->pid, current->comm);
	wait_for_completion(&comp);
	printk(KERN_ERR "awoken %i (%s)\n", current->pid, current->comm);

	return 0;
}
 
ssize_t complete_write(struct file *filp, const char __user *buf, size_t count, loff_t *pos)
{
	printk(KERN_ERR "process %i (%s) awakening the readers...\n", current->pid, current->comm);
	complete(&comp);

	return count;
}
 
struct file_operations complete_fops = {
	.owner = THIS_MODULE,
	.read = complete_read,
	.write = complete_write,
};
 
int complete_init(void)
{
	int result;
	result = register_chrdev(complete_major, "complete", &complete_fops);
	if(result < 0)
		return result;
	if(complete_major == 0)
		complete_major = result;
	return 0;
}
void complete_cleanup(void)
{
	unregister_chrdev(complete_major, "complete");
}

module_init(complete_init);
module_exit(complete_cleanup);
