#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/string.h>
#include <linux/semaphore.h>

#define DRIVER_AUTHOR "Dimitrios Vasilas <dimitrios.vasilas@scality.com>"
#define DRIVER_DESC "Eudyptula task08"

#define UID "afa9c09dcaae"
#define BUFFER_SIZE 13

static DEFINE_SEMAPHORE(fsem);
static char fdata[PAGE_SIZE];
static int flen;

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
			char *buf)
{
	down(&fsem);
	strncpy(buf, fdata, flen);
	up(&fsem);

	return flen;
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
			 const char *buf, size_t count)
{
	if (count > PAGE_SIZE)
		return -EINVAL;

	down(&fsem);
	strncpy(fdata, buf, count);
	flen = count;
	up(&fsem);

	return count;
}

static struct kobj_attribute foo_attribute =
	__ATTR_RW(foo);

static ssize_t id_show(struct kobject *kobj, struct kobj_attribute *attr,
		      char *buf)
{
	strncpy(buf, UID, BUFFER_SIZE);

	return BUFFER_SIZE;
}

static ssize_t id_store(struct kobject *kobj, struct kobj_attribute *attr,
		       const char *buf, size_t count)
{

	char *str = UID;

	if (count != BUFFER_SIZE)
		return -EINVAL;

	if (strncmp(str, buf, BUFFER_SIZE-1))
		return -EINVAL;

	return BUFFER_SIZE;
}

static struct kobj_attribute id_attribute =
	__ATTR(id, 0664, id_show, id_store);

static ssize_t jiffies_show(struct kobject *kobj,
		struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%lu\n", jiffies);
}

static struct kobj_attribute jiffies_attribute =
	__ATTR_RO(jiffies);


static struct attribute *attrs[] = {
	&foo_attribute.attr,
	&id_attribute.attr,
	&jiffies_attribute.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

static struct kobject *sysfsd_kobj;

static int __init example_init(void)
{
	int ret;

	sysfsd_kobj = kobject_create_and_add("eudyptula", kernel_kobj);
	if (!sysfsd_kobj)
		return -ENOMEM;

	ret = sysfs_create_group(sysfsd_kobj, &attr_group);
	if (ret)
		kobject_put(sysfsd_kobj);

	return ret;
}

static void __exit example_exit(void)
{
	kobject_put(sysfsd_kobj);
}

module_init(example_init);
module_exit(example_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
