#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main()
{
	char xd[] = "mais oui c est clai\' c est la congolexicomatisation des lois du ma\'che";
	int pipefd[2];
	char buf[1024];
	
	if(pipe(pipefd) == -1)exit(EXIT_FAILURE);
	int pid = fork();
	
	if(pid == -1)exit(EXIT_FAILURE);
	
	if(pid == 0)
	{
		close(pipefd[1]);
		wait(NULL);
		read(pipefd[0],buf,1024*sizeof(char));
		printf("%s\n",buf);
		close(pipefd[0]);
		
	}
	
	else
	{
		close(pipefd[0]);
		write(pipefd[1],xd,strlen(xd)*sizeof(char));
		close(pipefd[1]);
	}
	
	exit(EXIT_SUCCESS);
}



