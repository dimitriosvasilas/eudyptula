#include <linux/module.h>
#include <linux/poll.h>
#include <linux/debugfs.h>
#include <linux/semaphore.h>

#define UID "afa9c09dcaae"
#define BUFFER_SIZE 13

static DEFINE_SEMAPHORE(fsem);
static char fdata[PAGE_SIZE];
static int flen; 
static struct dentry *denstr;

ssize_t dfsd_id_read(struct file *fp, char __user *user, size_t size,
			loff_t *offs);

ssize_t dfsd_id_write(struct file *fp, const char __user *user, size_t size,
			loff_t *offs);

ssize_t dfsd_foo_read(struct file *fp, char __user *user, size_t size,
			loff_t *offs);

ssize_t dfsd_foo_write(struct file *fp, const char __user *user, size_t size,
			loff_t *offs);

static const struct file_operations dfsd_id_fops = {
	.owner = THIS_MODULE,
	.read = dfsd_id_read,
	.write = dfsd_id_write
};

static const struct file_operations dfsd_foo_fops = {
	.owner = THIS_MODULE,
	.read = dfsd_foo_read,
	.write = dfsd_foo_write
};

static int __init dfsd_init(void)
{
	denstr = debugfs_create_dir("dfsd", NULL);
	if (!denstr) {
		goto out;
	}

	if (!debugfs_create_file("id", 0666, denstr, NULL, &dfsd_id_fops)) {
		goto out;
	}

	if (!debugfs_create_u32("jiffies", 0444, denstr, (u32*)&jiffies)) {
		goto out;
	}

	if (!debugfs_create_file("foo", 0644, denstr, NULL, &dfsd_foo_fops)) {
		goto out;
	}


	pr_debug("Hello World!\n");
	return 0;

out:	
	pr_alert("Could not create devices");
	return -ENODEV;
}

static void __exit dfsd_exit(void)
{
	debugfs_remove_recursive(denstr);
}

ssize_t dfsd_id_read(struct file *fp, char __user *user, size_t size,
                        loff_t *offs)
{
	return simple_read_from_buffer(user, size, offs, UID,
					strlen(UID));
}

ssize_t dfsd_id_write(struct file *fp, const char __user *user, size_t size,
                        loff_t *offs)
{
	char buff[BUFFER_SIZE];
	int ret;

	ret = simple_write_to_buffer(buff, BUFFER_SIZE-1,
			offs, user, size);

	if (ret < -1) {
		return ret;
        }

	buff[BUFFER_SIZE - 1] = '\0';

	if ((*offs) != strlen(UID)) {
		return -EINVAL;
	}

	ret = strncmp(buff, UID, strlen(UID)) ? -EINVAL : 0;
	return ret;
}

ssize_t dfsd_foo_read(struct file *fp, char __user *user, size_t size,
			loff_t *offs)
{
	int ret = -EINVAL;

	if (*offs != 0) {
		return 0;
	}

	down(&fsem);

	if (!copy_to_user(user, fdata, flen)) {
		*offs += size;
		ret = size;
	}

	up(&fsem);

	return ret;
}

ssize_t dfsd_foo_write(struct file *fp, const char __user *user, size_t size,
		loff_t *offs)
{
	int ret = 0;
	if (size >= PAGE_SIZE) {
		return -EINVAL;
	}

	down(&fsem);

	if (copy_from_user(fdata, user, size)) {
		flen = 0;
	}
	else {
		flen = size;
		ret = size;
	}

	up(&fsem);

	return ret;
}

module_init(dfsd_init);
module_exit(dfsd_exit);

MODULE_LICENSE("GPL");
