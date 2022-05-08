#include <linux/module.h>
#include <linux/configfs.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/kd.h>
#include <linux/vt.h>
#include <linux/console_struct.h>
#include <linux/fs.h>
#include <linux/vt_kern.h>
#include <linux/kobject.h> 
#include <linux/sysfs.h> 

#define RESTORE_LEDS  0xFF

static struct kobject *kbleds_kobject;

struct tty_driver *kbleds_driver;

/* the variable you want to be able to change */ 
static int kbledstatus = 0;

static ssize_t kbledstatus_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) 
{ 
    return sprintf(buf, "%d\n", kbledstatus); 
} 
 
static ssize_t kbledstatus_store(struct kobject *kobj, struct kobj_attribute *attr, char *buf, size_t count) 
{ 
    sscanf(buf, "%du", &kbledstatus);

    if (kbledstatus >= 0 && kbledstatus < 8)
    {
        (kbleds_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, kbledstatus);
    }
    else
    {
        pr_info("kbleds: uncorrect value of arguments. It should be in [0, 7] \n");
    }

    return count; 
}

static struct kobj_attribute kbledstatus_attribute = __ATTR(kbledstatus, 0664, (void *)kbledstatus_show, (void *)kbledstatus_store); 

static int __init kbleds__init(void) 
{ 
    int error = 0; 
    int i;
 
    pr_info("kbleds: initialised\n"); 
 
    kbleds_kobject = kobject_create_and_add("kbleds", kernel_kobj); 
    if (!kbleds_kobject) 
        return -ENOMEM; 
 
    error = sysfs_create_file(kbleds_kobject, &kbledstatus_attribute.attr); 
    if (error) 
    { 
        pr_info("failed to create the myvariable file in /sys/kernel/kbleds\n"); 
    }

    printk(KERN_INFO "kbleds: loading\n");
    printk(KERN_INFO "kbleds: fgconsole is %x\n", fg_console);
    
    for (i = 0; i < MAX_NR_CONSOLES; i++)
    {
        if (!vc_cons[i].d)
            break;
        printk(KERN_INFO "poet_atkm: console[%i/%i] #%i, tty %lx\n", i,
               MAX_NR_CONSOLES, vc_cons[i].d->vc_num,
               (unsigned long)vc_cons[i].d->port.tty);
    }
    printk(KERN_INFO "kbleds: finished scanning consoles\n");
    
    kbleds_driver = vc_cons[fg_console].d->port.tty->driver;
    printk(KERN_INFO "kbleds: tty driver magic %x\n", kbleds_driver->magic);

    return error; 
} 
 
static void __exit kbleds__exit(void) 
{ 
    pr_info("kbleds: Exit success\n"); 
    kobject_put(kbleds_kobject); 
    (kbleds_driver->ops->ioctl) (vc_cons[fg_console].d->port.tty, KDSETLED, RESTORE_LEDS);
} 
 
module_init(kbleds__init); 
module_exit(kbleds__exit); 

MODULE_DESCRIPTION("Module illustrating the use of Keyboard LEDs using sysfs");
MODULE_LICENSE("GPL");