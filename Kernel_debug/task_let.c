#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

void tasklet_fun(unsigned long data);
//Step1 定义并静态初始化tasklet_struct 结构变量
DECLARE_TASKLET(mytasklet, tasklet_fun, 651);
//Step2 tasklet服务函数
void tasklet_fun(unsigned long data)
{
    static unsigned long count = 0;
    printk("count:%lu,%s is call! data:%lu\r\n",count++,__FUNCTION__,data);
    tasklet_schedule(&mytasklet); //在工作函数中重新调度自己，这样会循环调用tasklet_fun
}
static int __init mytasklet_init(void)
{
    //Step3 开始调度 mytasklet
    tasklet_schedule(&mytasklet);
    printk("%s is call!\r\n",__FUNCTION__);
    return 0;
}
static void __exit mytasklet_exit(void) //Module exit function specified by module_exit()
{
    //Step4 删除 tasklet
    tasklet_kill(&mytasklet);
}
module_init(mytasklet_init);
module_exit(mytasklet_exit);
MODULE_LICENSE("GPL");
