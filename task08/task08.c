#include <linux/module.h>
#include <linux/poll.h>
#include <linux/debugfs.h>
#include <linux/semaphore.h>

#define DRIVER_AUTHOR "Dimitrios Vasilas <dimitrios.vasilas@scality.com>"
#define DRIVER_DESC "Eudyptula task08"

#define UID "afa9c09dcaae"
#define BUFFER_SIZE 13

static DEFINE_SEMAPHORE(fsem);
static char fdata[PAGE_SIZE];
static int flen; 
static struct dentry *denstr;

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

static const struct file_operations dfsd_foo_fops = {
	.owner = THIS_MODULE,
	.read = dfsd_foo_read,
	.write = dfsd_foo_write
};

ssize_t dfsd_id_read(struct file *fp, char __user *user, size_t size,
                        loff_t *offs)
{
        if (*offs != 0)
                return 0;

        if (copy_to_user(user, UID, BUFFER_SIZE))
                return -EINVAL;

        *offs += size;

        return size;
}

ssize_t dfsd_id_write(struct file *fp, const char __user *user, size_t size,
                        loff_t *offs)
{
        char *str = UID;
        char buff[BUFFER_SIZE];

        if (size != BUFFER_SIZE ||
                copy_from_user(buff, user, BUFFER_SIZE-1) ||
                strncmp(buff, str, BUFFER_SIZE - 1))
                return -EINVAL;

        return size;
}

static const struct file_operations dfsd_id_fops = {
        .owner = THIS_MODULE,
        .read = dfsd_id_read,
        .write = dfsd_id_write
};

static int __init dfsd_init(void)
{
	denstr = debugfs_create_dir("eudyptula", NULL);
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

module_init(dfsd_init);
module_exit(dfsd_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
