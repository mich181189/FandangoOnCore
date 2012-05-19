/* fandango.c - The FAC (Fandango On Core) Kernel module
** 
** (c) 2012 Michael Cullen. 
** With help from http://tldp.org/HOWTO/Module-HOWTO/x839.html
** Note: The purpose of this IS to take down the machine if an app crashes!
**
*/

#define __KERNEL__         /* We're part of the kernel */
#define MODULE             /* Not a permanent part, though. */

#include <linux/modversions.h> 
#include <linux/module.h>  
#include <linux/tty.h>

int init()
{
	printk("Fandango module reporting for duty and ready to DANCE!\n");
	printk("Or not as it's not written yet.\n");
}

void cleanup()
{
  printk("Fandango module sitting down for a rest. (unloading)\n");
}

module_init(init);
module_exit(cleanup);

MODULE_AUTHOR("Michael Cullen");
MODULE_LICENSE("GPL");
MODULE_VERSION("1:0.0") ;
MODULE_DESCRIPTION("Make application crashes more fun!");