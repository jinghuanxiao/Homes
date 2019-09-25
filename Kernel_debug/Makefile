ifneq ($(KERNELREALSE),)
	obj-m :=hello.o world.o
	hello-y := debug.o test.o 
else
	KERNELDIR :=/lib/modules/$(shell uname -r)/build
	PWD :=$(shell pwd)
	obj-m :=hello.o world.o
	hello-y := debug.o test.o

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

endif
