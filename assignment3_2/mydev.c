#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

static char dev_buf[100] = "";
const char *dev_name = "mydev";

static uint32_t open_instances = 0;

// Function Declarations
int mydev_open(struct inode *inodep, struct file *fileptr);
ssize_t mydev_read(struct file *fileptr, char *user_buff, size_t len, loff_t *off);
ssize_t mydev_write(struct file *fileptr, const char *user_buff, size_t len, loff_t *off);
int mydev_close(struct inode *inodeptr, struct file *fileptr);

struct file_ops fops ={
	.read = mydev_read,
	.write = mydev_write,
	.open = mydev_open,
	.release = mydev_close
};

static int __init mydev_init(void){
	register_chrdev(250, dev_name, &fops);
	printk(KERN_INFO "Device %s connected\n", dev_name);
	return 0;
}

static void __exit mydev_exit(void){
	unregister_chrdev(250, dev_name);
	printk(KERN_INFO "Device %s disconnected\n", dev_name);
}

int mydev_open (struct inode *inodep, struct file *fileptr){
	printk(KERN_INFO "Device file opened for %s", dev_name);
	open_instances += 1;
}

ssize_t mydev_read(struct file *fileptr, char *user_buff, size_t len, loff_t *off){
	ssize_t count = 0;
	while(dev_buf[count] != '\0')
	{
		put_user(dev_buf[count], user_buff++);
		count++;
	}
	put_user("\0", user_buff++);
	return count;
}

ssize_t mydev_write(struct file *fileptr, const char *user_buff, size_t len, loff_t *off){
	ssize_t count = 0;
	size_t written = len - 1;
	memset(dev_buf, 0, 100);
	while(written >= 0){
		dev_buf[written] = user_buff[count];
		count++;
		written--;
	}
	dev_buf[len] = "\0";
	return count;
}

int mydev_close(struct inode *inodeptr, struct file *fileptr)
{
	count--;
	printk(KERN_INFO "Device file closed for %s", dev_name);
	return count;
}

module_init(mydev_init);
module_exit(mydev_exit);