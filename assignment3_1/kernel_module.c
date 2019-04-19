#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manas Mulay");

void print_proc_info(void){
	struct task_struct* task_list;
        size_t process_counter = 0;
	size_t tasks_running = 0;
	size_t percentage; 
	for_each_process(task_list) {
                ++process_counter;
                if(task_list->state == 0x0000)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_RUNNING\n",task_list->pid, task_list->parent->pid);
					tasks_running += 1;
				}
				else
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_INTERRUPTIBLE\n",task_list->pid, task_list->parent->pid);
				}
        }
	percentage = tasks_running*100;
	percentage /= process_counter;
	printk(KERN_INFO "TASK_RUNNING percent = %lu\n", percentage);
}

static int hello_init(void){
	printk(KERN_ALERT "Init\n");
	print_proc_info();
	return 0;
}

static void hello_exit(void){
	printk(KERN_ALERT "Exit\n");
}

module_init(hello_init);
module_exit(hello_exit);