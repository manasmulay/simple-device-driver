#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

static char dev_buf[100] = "";
const char *dev_name = "mydevice_driver";

static uint32_t open_instances = 0;

// Function Declarations
int mydev_open(struct inode *inodep, struct file *fileptr);
ssize_t mydev_read(struct file *fileptr, char *user_buff, size_t len, loff_t *off);
ssize_t mydev_write(struct file *fileptr, const char *user_buff, size_t len, loff_t *off);
int mydev_close(struct inode *inodeptr, struct file *fileptr);

struct file_operations fops = {
	.read = mydev_read,
	.write =  mydev_write,
	.open = mydev_open,
	.release = mydev_close
};

static int __init mydev_init(void){
	int t = register_chrdev(25, dev_name, &fops);
	if(t < 0) printk(KERN_INFO "Device Error\n");
	printk(KERN_INFO "Device %s connected\n", dev_name);
	return 0;
}

static void __exit mydev_exit(void){
	unregister_chrdev(25, dev_name);
	printk(KERN_INFO "Device %s disconnected\n", dev_name);
}

int mydev_open (struct inode *inodep, struct file *fileptr){
	printk(KERN_INFO "Device file opened for %s", dev_name);
	open_instances += 1;
	return open_instances;
}

ssize_t mydev_read(struct file *fileptr, char *user_buff, size_t len, loff_t *off){
	short count = 0;
	short readPos = 0;
	while(len && dev_buf[readPos] != 0)
	{
		put_user(dev_buf[readPos], user_buff++);
		count++;
		readPos++;
		len--;
	}
	return count;
}

ssize_t mydev_write(struct file *fileptr, const char *user_buff, size_t len, loff_t *off){
	short ind = len - 1;
	short count = 0;
	memset(dev_buf,0,100);
	while(len > 0)
	{
		dev_buf[count++] = user_buff[ind--];
		len--;
	}
	return count;
}

int mydev_close(struct inode *inodeptr, struct file *fileptr)
{
	open_instances--;
	printk(KERN_INFO "Device file closed for %s", dev_name);
	return open_instances;
}

module_init(mydev_init);
module_exit(mydev_exit);
