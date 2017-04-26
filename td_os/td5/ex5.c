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
	char buf[1024];
	
	int pipefd[2];
	if(pipe(pipefd) == -1)exit(EXIT_FAILURE);
	
	int i,nbr_fini = 0;
	for(i=0;i<nbr_thread;i++)
	{
		if(fork())break;
	}
	
	if(i == nbr_thread) //pere
	{
		close(pipefd[1]);
		
		while(nbr_fini<nbr_thread)
		{
			
		}
		close(pipefd[0]);
	}
	else //fils
	{
		close(pipefd[0]);
		
		if(rand()%100<50) //abonnement
		{
			
		}
		if(rand()%100<30) //message
		{
			
		}
		if(rand()%100<20) //liste
		{
			
		}
		
		
		
		close(pipefd[1]);
	}
	exit(0);
}

