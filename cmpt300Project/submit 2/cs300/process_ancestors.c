#include "process_ancestors.h"
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/list.h>
#include <linux/uidgid.h> /*  header for call function to convert uid to long int */

asmlinkage long sys_process_ancestors(struct process_info info_array[], long size, long *num_filled)
{
	
	long count_filled = 0;
	long count_children ;
	long count_sibling ;
	long result = 0;
	
	long name_index;

	struct task_struct *task_temp = current;
	
	
	struct list_head *children_head ;
	struct list_head *sibling_head ;
	

	struct process_info pinfo;

	pinfo.pid = 0;
   pinfo.name[0] = '\0';
   pinfo.state = 0;                  
	pinfo.uid = 0;                     
	pinfo.nvcsw = 0;                 
   pinfo.nivcsw = 0;                 
 	pinfo.num_children = 0;            
	pinfo.num_siblings = 0;

	if(size <= 0)
	{
		return -EINVAL;
	}
	else
	{
		
   		while( (task_temp->parent != task_temp) && (count_filled < size) )
   		{

   			name_index = 0;
            count_children = 0;
            count_sibling = 0;


   			pinfo.pid = task_temp->pid;

   			while(name_index < TASK_COMM_LEN)
   			{
   				pinfo.name[name_index] = task_temp->comm[name_index];
   				name_index++;
   			}
   			
   			pinfo.state = task_temp->state;
   			pinfo.uid = task_temp->cred->uid.val;/*__kuid_val(task_temp->cred->uid);*/
   			pinfo.nvcsw = task_temp->nvcsw;
   			pinfo.nivcsw = task_temp->nivcsw;


   			
   		

   			
   			list_for_each(children_head, &(task_temp->children))
   			{
   				count_children++;
   			}
   			list_for_each(sibling_head , &(task_temp->sibling))
   			{
   				count_sibling++;
   			}

   			pinfo.num_children = count_children;
            if(task_temp->pid != 1)
            {
               pinfo.num_siblings = count_sibling - 1;
            }
            else
            {
               pinfo.num_siblings =0;
            }
   			
			


   			if(copy_to_user(&info_array[count_filled] , &pinfo, sizeof(pinfo)) != 0 )
   			{
   				return -EFAULT;
   			}
   			else
   			{
   				/*if(copy_to_user(&size, &count_size, sizeof(count_size)) !=0)
   				{
   					return -EFAULT;
   				}
   				else
   				{*/
   					if(copy_to_user(num_filled, &count_filled, sizeof(count_filled)) != 0 )
   					{
   						return -EFAULT;
   					}
   					else
   					{
   						count_filled++;
   					}
   				
   			}



   			task_temp = task_temp->parent;

   			/*print section to see result */
   			printk("\n\nDisplay infomation about  entry %ld of preocess info array", count_filled);
   			printk("\n");
   			printk("%15s%21s%16s%16s%16s%16s%16s%16s\n", "Process ID", "Process Name", "Process State", "Process Uid", "Process nvcsw", "Process nivcsw", "# of children", "# of sibling");
   			printk("%15ld%21s%16ld%16ld%16ld%16ld%16ld%16ld\n", pinfo.pid, pinfo.name, pinfo.state, pinfo.uid, pinfo.nvcsw, pinfo.nivcsw, pinfo.num_children, pinfo.num_siblings);
   		}

	}
	

   	return result;	        
}