#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define nbr_process 20

int main(int argc, char** argv)
{
	int tmp,pid;
	int return_value;
	int i;
	
	for(i=1;i<=nbr_process;i++)
	{
		pid = fork();
		if(pid == -1)exit(0);
		if(pid == 0)break;
	}
	
	if(pid == 0)
	{
		exit(getpid() % 10);
	}
	
	else
	{
		for(i=0;i<nbr_process;i++)
		{
			tmp = wait(&return_value);
			
			printf("pid fils : %d\n",tmp);
			printf("return_value : %d\n",WEXITSTATUS(return_value));
		}
	}
	
	exit(0);
}
