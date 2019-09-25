#ifndef __KERNEL__
#  define __KERNEL__
#endif
#ifndef MODULE
#  define MODULE
#endif

// 下面的是主要的内容
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int year=2012;

static int __init hello_init(void)
{
    printk(KERN_WARNING "Hello kernel, it's %d!\n",year);
    return 0;
}


static void __exit hello_exit(void)
{
    printk("Bye, kernel!\n");
}


module_init(hello_init);
module_exit(hello_exit);
