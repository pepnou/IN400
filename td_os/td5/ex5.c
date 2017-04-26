#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define nbr_thread 20



int main()
{
	srand(time(NULL));
	
	int pipefd[2];
	if(pipe(pipefd) == -1)exit(EXIT_FAILURE);
	
	int i;
	for(i=0;i<nbr_thread;i++)
	{
		if(fork())break;
	}
	
	
	
	if(i == nbr_thread) //pere
	{
		
		
		for(i=0;i<nbr_thread;i++) wait();
	}
	else //fils
	{
		
		
		
	}
	
}

