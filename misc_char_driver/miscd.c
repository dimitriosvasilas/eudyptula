#include <linux/module.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "miscd"
#define UID "afa9c09dcaae"
#define BUFFER_SIZE 13

ssize_t miscd_read(struct file *fp, char __user *user, size_t size,
			loff_t *offs);

ssize_t miscd_write(struct file *fp, const char __user *user, size_t size,
			loff_t *offs);

static const struct file_operations miscd_fops = {
	.owner = THIS_MODULE,
	.read = miscd_read,
	.write = miscd_write
};

static struct miscdevice miscd_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &miscd_fops,
};

static int __init miscd_init(void)
{
	return misc_register(&miscd_misc);
}

static void __exit miscd_exit(void)
{
	misc_deregister(&miscd_misc);
	return;
}

ssize_t miscd_read(struct file *fp, char __user *user, size_t size,
                        loff_t *offs)
{		
	return simple_read_from_buffer(user, size, offs, UID,
				strlen(UID));
}
ssize_t miscd_write(struct file *fp, const char __user *user, size_t size,
                        loff_t *offs)
{
	char buff[BUFFER_SIZE];
	int ret = -1;
	
	if (size != BUFFER_SIZE)
		return -EINVAL;
	
	simple_write_to_buffer(buff, BUFFER_SIZE-1,
			offs, user, size);
	buff[BUFFER_SIZE - 1] = '\0';

	if ((*offs) != strlen(UID))
		return -EINVAL;

	ret  = strncmp(buff, UID, strlen(UID)) ? -EINVAL : 0;
	return ret;
}

module_init(miscd_init);
module_exit(miscd_exit);
MODULE_LICENSE("GPL");
