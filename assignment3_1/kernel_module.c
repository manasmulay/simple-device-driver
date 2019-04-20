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
	size_t task_state; 
	for_each_process(task_list) {
                ++process_counter;
                task_state = task_list->state;
                if(task_state == TASK_RUNNING)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_RUNNING\n",task_list->pid, task_list->parent->pid), task_list->state;
					tasks_running += 1;
				}
				else if(task_state == TASK_INTERRUPTIBLE)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_INTERRUPTIBLE\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_UNINTERRUPTIBLE)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_UNINTERRUPTIBLE\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == __TASK_STOPPED)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : __TASK_STOPPED\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == __TASK_TRACED)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : __TASK_TRACED\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_PARKED)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_PARKED\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_DEAD)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_DEAD\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_WAKEKILL)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_WAKEKILL\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_WAKING)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_WAKING\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_NOLOAD)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_NOLOAD\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_NEW)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_NEW\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_STATE_MAX)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_STATE_MAX\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_IDLE)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_KILLABLE\n",task_list->pid, task_list->parent->pid);
				}
				else if(task_state == TASK_IDLE)
				{
					pr_info("PID [%d] running, Parent PID [%d], State : TASK_IDLE\n",task_list->pid, task_list->parent->pid);
				}
				else
				{
					pr_info("PID [%d] running, Parent PID [%d], State : %zu\n",task_list->pid, task_list->parent->pid, task_list->state);
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
