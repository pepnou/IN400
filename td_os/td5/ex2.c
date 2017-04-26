#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define nbr_thread 20

void transmission(int pipel, int n)
{
	char buf[1024];
	read(pipel,buf,1024*sizeof(char));
	
	//printf("%s\n",buf);
	
	if(n==nbr_thread)
	{
		printf("%s\n",buf);
		exit(0);
	}
	
	
	int pipefd[2];
	
	if(pipe(pipefd) == -1)exit(EXIT_FAILURE);
	
	int pid = fork();
	
	if(pid == -1)exit(EXIT_FAILURE);
	
	if(pid == 0)
	{
		close(pipefd[0]);
		write(pipefd[1],buf,1024*sizeof(char));
		close(pipefd[1]);
		
		wait(NULL);
	}
	
	else
	{
		close(pipefd[1]);
		n++;
		transmission(pipefd[0],n);
		//~ read(pipefd[0],buf,1024*sizeof(char));
		close(pipefd[0]);
		exit(0);
	}
	
}

int main()
{
	char* xd = malloc(sizeof(char)*3);
	xd[0] = 'o';
	xd[1] = 'k';
	xd[2] = '\0';
	int pipefd[2];
	int n = 1;
	
	if(pipe(pipefd) == -1)exit(EXIT_FAILURE);
	int pid = fork();
	
	if(pid == -1)exit(EXIT_FAILURE);
	
	if(pid == 0)
	{
		close(pipefd[0]);
		write(pipefd[1],xd,(strlen(xd)+1)*sizeof(char));
		close(pipefd[1]);
		
		wait(NULL);
	}
	
	else
	{
		close(pipefd[1]);
		transmission(pipefd[0],n);
		close(pipefd[0]);
	}
	
	exit(EXIT_SUCCESS);
}
