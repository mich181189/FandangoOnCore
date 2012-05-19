/* fandango.c - The FAC (Fandango On Core) Kernel module
** 
** (c) 2012 Michael Cullen. 
** With help from http://tldp.org/HOWTO/Module-HOWTO/x839.html
** Note: The purpose of this IS to take down the machine if an app crashes!
**
*/
#include <config/modversions.h> 
#include <linux/module.h>  
#include <linux/mm.h> // for si_meminfo
#include <asm/page.h> //for PAGE_SHIFT
#include <linux/random.h> //for get_random_bytes
#include <asm/io.h> //for pointer translations

long frandom() {
      long val;
      get_random_bytes(&val,sizeof(long));
      return val;
}

void* random_pointer() {
	struct sysinfo si;
	si_meminfo(&si);
	void* ptr = si.totalram << PAGE_SHIFT;
	ptr = (long)frandom() % (long)ptr;
	return ptr;
}

void fandango() {
	int num = 5;
	struct sysinfo si;
	si_meminfo(&si);
	void* ptr = random_pointer();
	int data = (int)frandom();
	printk("Page offset is %p and data is at %p physically \n",PAGE_OFFSET,virt_to_phys(&data));
	printk("Max pointer is %p\n",si.totalram << PAGE_SHIFT);
	printk("(would) Dancing on pointer %p (virtually %p) with the number %d\n",ptr,phys_to_virt(ptr),data);
	//*((int*)phys_to_virt(ptr)) = data; //the business end of the fandango!
}

int init()
{
	struct sysinfo si;
	int i;//for for loop
	si_meminfo(&si);
	printk("Fandango module reporting for duty and ready to DANCE!\n");
	printk("Or not as it's not written yet. Though there is %ld bytes of memory here!\n",si.totalram << PAGE_SHIFT);
	//for(i=0;i<10000;i++)
	  fandango();
	return 0;
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