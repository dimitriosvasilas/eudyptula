#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

static struct usb_device_id usbk_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
		USB_INTERFACE_SUBCLASS_BOOT,
		USB_INTERFACE_PROTOCOL_KEYBOARD)},
	{ }
};

static int __init init(void)
{
	pr_debug("Hello World!\n");
	return 0;
}

static void __exit usbk_exit(void)
{
	return;
}

MODULE_DEVICE_TABLE(usb, usbk_table);
module_init(init);
module_exit(usbk_exit);

MODULE_LICENSE("GPL");
