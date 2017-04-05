#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int pipefd[2];
	if(!pipe(pipefd))exit(EXIT_FAILURE);
	
	int pid = fork();
	
	if(pid == -1)exit(EXIT_FAILURE);
	
	if(pid == 0)
	{
		
	}
	
	else
	{
		
	}
	
	exit(EXIT_SUCCESS);
}
