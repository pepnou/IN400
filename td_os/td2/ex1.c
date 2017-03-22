#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	int pid;
	int ppid;
	int return_value;
	
	pid = fork();
	if(pid == -1) exit(-1);
	else if(pid == 0)
	{
		pid = getpid();
		ppid = getppid();
		
		printf("fils :\n");
		printf("pid : %d\n",pid);
		printf("ppid : %d\n",ppid);
		
		exit(pid % 10);
	}
	else
	{
		wait(&return_value);
		
		printf("pere :\n");
		printf("pid fils : %d\n",pid);
		printf("return_value : %d\n",WEXITSTATUS(return_value));
	}
	
	exit(0);
}
