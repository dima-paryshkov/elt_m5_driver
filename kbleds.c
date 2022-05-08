#include <linux/module.h>
#include <linux/configfs.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <linux/console_struct.h>
#include <linux/fs.h>
#include <linux/kobject.h> 
#include <linux/sysfs.h> 

static struct kobject *kbleds_kobject;

/* the variable you want to be able to change */ 
static int kbledstatus = 0;

static ssize_t kbledstatus_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) 
{ 
    return sprintf(buf, "%d\n", kbledstatus); 
} 
 
static ssize_t kbledstatus_store(struct kobject *kobj, struct kobj_attribute *attr, char *buf, size_t count) 
{ 
    sscanf(buf, "%du", &kbledstatus); 
    return count; 
}

static struct kobj_attribute kbledstatus_attribute = __ATTR(kbledstatus, 0664, (void *)kbledstatus_show, (void *)kbledstatus_store); 

static int __init kbleds__init(void) 
{ 
    int error = 0; 
 
    pr_info("kbleds: initialised\n"); 
 
    kbleds_kobject = kobject_create_and_add("kbleds", kernel_kobj); 
    if (!kbleds_kobject) 
        return -ENOMEM; 
 
    error = sysfs_create_file(kbleds_kobject, &kbledstatus_attribute.attr); 
    if (error) 
    { 
        pr_info("failed to create the myvariable file in /sys/kernel/mymodule\n"); 
    } 
 
    return error; 
} 
 
static void __exit kbleds__exit(void) 
{ 
    pr_info("kbleds: Exit success\n"); 
    kobject_put(kbleds_kobject); 
} 
 
module_init(kbleds__init); 
module_exit(kbleds__exit); 

MODULE_DESCRIPTION("Module illustrating the use of Keyboard LEDs using sysfs");
MODULE_LICENSE("GPL");