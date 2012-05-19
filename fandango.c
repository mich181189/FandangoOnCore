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

int init_module()
{
	console_print("Fandango module reporting for duty and ready to DANCE!\n");
	console_print("Or not as it's not written yet.\n");
}

void cleanup_module()
{
  console_print("Fandango module sitting down for a rest. (unloading)\n");
}