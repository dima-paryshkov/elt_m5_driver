ifneq ($(KERNELRELEASE),)
	obj-m := kernel_space.o
else

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
	rm user_space

user_space : user_space.c 
	gcc user_space.c -o user_space -w