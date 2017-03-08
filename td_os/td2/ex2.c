#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define nbr_process 20

int main(int argc, char** argv)
{
	int pid[nbr_process];
	int return_value;
	int i;
	
	for(i=0;i<nbr_process;i++) pid[i] = fork();
	
	for(i=0;i<nbr_process;i++)
	{
		if(pid[i] == -1) exit(-1);
		
		else if(pid[i] == 0)
		{
			exit(pid[i] % 10);
		}
		
		else
		{
			wait(&return_value);
			
			printf("pid fils %d : %d\n",i,pid[i]);
			printf("return_value : %d\n",WEXITSTATUS(return_value));
		}
	}
	
	exit(0);
}
