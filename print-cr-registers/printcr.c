#include "linux/init.h"
#include "linux/module.h"

static int __init dumb_init(void)
{
    u64 cr0, cr2, cr3, cr4;

    /* 
    * mov  %%cr_, %0 doesn't work;
    * movq %%cr_, %0 doesn't work;
    * 
    * Why? That is the question.
    * Because of that, tmp register 
    * has to be used, I use r12.
    */
    __asm__ __volatile__ (
        "mov %%cr0, %%r12 \n\t"
        "mov %%r12, %0     \n\t"
        "mov %%cr2, %%r12  \n\t"
        "mov %%r12, %1     \n\t"
        "mov %%cr3, %%r12  \n\t"
        "mov %%r12, %2     \n\t"
        "mov %%cr4, %%r12  \n\t"
        "mov %%r12, %2     \n\t"

        : "=m" (cr0), "=m" (cr2), 
          "=m" (cr3), "=m" (cr4)
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