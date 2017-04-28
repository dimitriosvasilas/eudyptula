CFLAGS_skdrv.o = -DDEBUG
CONFIG_MODULE_SIG=n

KDIR ?= /lib/modules/$(shell uname -r)/build

obj-m += usb_keyboard.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
