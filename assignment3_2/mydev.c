#include <linux/kernel.h>
#include <linux/module.h>

static char device_buf[100] = "";

int register_chrdev(unsigned int major, const char *name, struct file_operations *fops);
int unregister_chrdev(unsigned int major, const char*name);

ssize_t mydev_read(struct file *fileptr, char *user_buffer, size_t len, loff_t *off){
	
}
ssize_t mydev_write (struct file *, const char *user_buff, size_t loff_t *);
int mydev_open (struct inode *, struct file *);
int mydev_close(struct inode *, struct file *);

static int __init mydev_init(void){
	register_chrdev();
	return 0;
}


static void __exit mydev_exit(void){
	unregister_chrdev();
}

struct file_ops fops ={
	.read = mydevice_read,
	.open = mydevice_open,
	.release = mydevice_close,
	.write = mydevice_write,
};
module_init(mydev_init);
module_exit(mydev_exit);
