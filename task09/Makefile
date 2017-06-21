CFLAGS_task09.o = -DDEBUG
CONFIG_MODULE_SIG=n

KDIR ?= /lib/modules/$(shell uname -r)/build

obj-m += task09.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
