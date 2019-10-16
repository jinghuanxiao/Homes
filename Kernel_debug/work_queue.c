#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/sysfs.h>
#include <linux/ctype.h>
#include <linux/workqueue.h>
#include <linux/delay.h>

 //工作以队列结构组织成工作队列（workqueue），其数据结构为workqueue_struct，
static struct workqueue_struct *test_wq = NULL;

//把推后执行的任务叫做工作（work），描述它的数据结构为work_struct
static struct work_struct   work;

/*
 *定义工作队列调用函数
 */
void work_func(struct work_struct *work)
{

        while(1){
                printk(KERN_ERR "-----%s-----\n",__func__);  //printk可以在多处理器上同时被调用
        }
}


static int __init test_init(void)
{

        /*创建工作队列workqueue_struct，该函数会为cpu创建内核线程*/
        test_wq = create_singlethread_workqueue("test_wq");

        /*初始化工作work_struct，指定工作函数*/
        INIT_WORK(&work,work_func);

        /*将工作加入到工作队列中，最终唤醒内核线程*/
        queue_work(test_wq, &work);

        while(1){
                mdelay(1000);
                printk(KERN_ERR "-----%s-----\n",__func__);
        }

        return 0;
}


static void __exit test_exit(void){

}

module_init(test_init);
module_exit(test_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liujin725@outlook.com");
