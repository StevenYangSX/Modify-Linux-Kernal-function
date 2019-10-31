// Test application for the array_stats syscall.

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "process_ancestors.h"

// Sys-call number:
#define _PROCESS_ANCESTORS_ 342

int main(int argc, char *argv[])
{
	/* code */
	long a = 0;
	long *num_filled = &a ;
	struct process_info *info_array;
	info_array = malloc(8 * sizeof(info_array));
	printf("\nDiving to kernel level\n\n");
	syscall (_PROCESS_ANCESTORS_, info_array, 8, num_filled);
	/*for(int i = 0 ; i<8; i++)
	{
		printf("pid of process %d is %ld\n", i,info_array[i].pid);
		printf("name of process %d is %s\n",i, info_array[i].name);
		printf("state of process %d is %ld\n", i ,info_array[i].state);
		printf("uid of process %d is %ld\n", i,info_array[i].uid);
		printf("nvcsw of process %d is %ld\n",i, info_array[i].nvcsw);
		printf("nivcsw of process %d is %ld\n",i, info_array[i].nivcsw);
		printf("# of children of process %d is %ld\n",i, info_array[i].num_children);
		printf("# of sibling of process %d is %ld\n", i,info_array[i].num_siblings);
	}
	//printf("\n what?%d\n", result); */
	printf("\nRising to user level\n");
	return 0;
}