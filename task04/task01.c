#include <linux/module.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "Dimitrios Vasilas <dimitrios.vasilas@scality.com>"
#define DRIVER_DESC "Eudyptula task01"

static int __init init(void)
{
	pr_debug("Hello World!");
	return 0;
}

static void __exit fini(void)
{
		return;
}

module_init(init);
module_exit(fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
