#include "linux/init.h"
#include "linux/module.h" 

static int __init dumb_init(void)
{
    u64 cr0, cr2, cr3, cr4;

    __asm__ __volatile__ (
        "mov %%cr0, %0     \n\t"
        "mov %%cr2, %1     \n\t"
        "mov %%cr3, %2     \n\t"
        "mov %%cr4, %3     \n\t"
    
        : "=r" (cr0), "=r" (cr2), 
          "=r" (cr3), "=r" (cr4)
        : /* no input */
        : /* no clobbers */
    );

    printk(KERN_INFO "cr0 = %016llx\n", cr0);
    printk(KERN_INFO "cr2 = %016llx\n", cr2);
    printk(KERN_INFO "cr3 = %016llx\n", cr3);
    printk(KERN_INFO "cr4 = %016llx\n", cr4);
    return 0;
}

static void __exit dumb_exit(void)
{

}

module_init(dumb_init);
module_exit(dumb_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Dmitry Voevodskiy");
MODULE_DESCRIPTION("Prints cr_ register values");
MODULE_VERSION("1:1.0");