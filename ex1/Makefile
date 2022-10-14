CONFIG_MODULE_SIG=n

obj-m				+= ioctl-test.o
ioctl-test-objs			:= ioctl.o

#CC=gcc
KVERSION = $(shell uname -r)
KERNEL_DIR := /lib/modules/$(KVERSION)/build

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
