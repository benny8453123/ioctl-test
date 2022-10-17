CONFIG_MODULE_SIG=n

obj-m						+= chardev-ioctl-test.o
chardev-ioctl-test-objs		:= chardev2.o

#CC=gcc
KVERSION = $(shell uname -r)
KERNEL_DIR := /lib/modules/$(KVERSION)/build

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
