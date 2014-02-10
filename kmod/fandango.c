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
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>

struct proc_dir_entry *fandango_proc;

long frandom() {
      long val;
      get_random_bytes(&val,sizeof(long));
      return val;
}

void* random_pointer() {
	struct sysinfo si;
	si_meminfo(&si);
	void* ptr = si.totalram << PAGE_SHIFT;
	ptr = ((long)frandom() % (unsigned long)(ptr-33554432))+33554432; //as in, 0x2000000 in hex. Seems to work as an offset.
	return ptr;
}

void fandango() {
	int i = 0;
	struct sysinfo si;
	si_meminfo(&si);
	void* ptr = random_pointer();
	int data = (int)frandom();
	printk(KERN_CRIT,"Fandango: Dancing on pointer %p (virtually %p) with the number %d\n",ptr,phys_to_virt(ptr),data);
	while(i < 1024) {
	  *((int*)phys_to_virt(ptr++)) = (char)data; //the business end of the fandango! Chose a chunk of memory and wipe it out!
	}
}

int procfile_read(struct file *filp,char *buf,size_t count,loff_t *offp ) 
{
	static const char* message = "Fandango is currently in demo mode\n";

	if(*offp > strlen(message))
		return 0;

	if(count > (strlen(message)-*offp))
		count = strlen(message)-(*offp);
	
	size_t ret = copy_to_user(buf,message+*offp,count);
	*offp = *offp+count-ret;

	return count-ret;
}

int procfile_write(struct file *filp, const char *buf, size_t count, loff_t *offp)
{
	for(size_t i = 0;i<count;++i)
	{
		if(buf[i] == '4')
		{
			//printk("Would fandango right about now\n");
			fandango();
		}
	}
	*offp += count;
	return count;
}

struct file_operations proc_fops = {
read: procfile_read,
write: procfile_write
};

int init()
{
	struct sysinfo si;
	int i;//for for loop
	si_meminfo(&si);
	printk(KERN_INFO,"Fandango module reporting for duty and ready to DANCE!\n");

	//setup proc
	proc_create("fandango",0666,NULL,&proc_fops);

	return 0;
}

void cleanup()
{
  printk(KERN_INFO,"Fandango module sitting down for a rest. (unloading)\n");
  remove_proc_entry("fandango",NULL);
}

module_init(init);
module_exit(cleanup);

MODULE_AUTHOR("Michael Cullen");
MODULE_LICENSE("GPL");
MODULE_VERSION("1:0.0") ;
MODULE_DESCRIPTION("Make application crashes more fun!");