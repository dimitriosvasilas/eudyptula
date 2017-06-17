CONFIG_MODULE_SIG=n
CFLAGS_task01.o = -DDEBUG

KDIR ?= /lib/modules/$(shell uname -r)/build

obj-m += task01.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

