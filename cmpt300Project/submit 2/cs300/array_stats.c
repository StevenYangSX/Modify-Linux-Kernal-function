#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include "array_stats.h"
#include <linux/errno.h>
#include <linux/slab.h>



asmlinkage long sys_array_stats(struct array_stats *stats, long data[], long size)
{
	long result = 0;
	long counter = 0;
	struct array_stats array;
	array.min = 0;
	array.max = 0;
	array.sum = 0;

	
	
	
	if(size <= 0 )
		return -EINVAL;
	else
	{
		
		while(counter < size)
		{
			long temp = 0;
			if(copy_from_user(&temp, &data[counter], sizeof(data[counter]) ) !=0)
			{
				return -EFAULT;
			}
			else
			{
				if(counter ==0)
				{
					array.min = temp;
					array.max = temp;
				}
				
				if(counter > 0)
				{
					if(temp > array.max)
						array.max = temp;
					if(temp < array.min)
						array.min = temp;
				}
			}

			array.sum = (array.sum + temp);
			
			counter++;
		
		}
	}

	if(copy_to_user(stats, &array, sizeof(array)) != 0)
	{
		return -EFAULT;
	}
	else
	{
		return result ;
	}
	
}
