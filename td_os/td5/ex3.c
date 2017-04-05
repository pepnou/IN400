#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define INCREMENT 1024

int taille;

void afficher(int signo)
{
	printf("%d octet\n",taille);
	exit(0);
}

int main()
{
	char buf[INCREMENT];
	int pipefd[2];
	struct sigaction sa;
	
	pipe(pipefd);
	
	taille = 0;
	
	sa.sa_handler = afficher;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	
	if(sigaction(SIGALRM,&sa,NULL) == 1)
	{
		perror("sigaction");
		exit(1);
	}
	
	alarm(4);
	while(1)
	{
		write(pipefd[1],buf,INCREMENT);
		taille += INCREMENT;
	}
}
