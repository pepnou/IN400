#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc,char** argv)
{
	int pid;
	struct tms tmp;
	int status;
	
	if(argc == 1)exit(0);
	
	char* commande1 = malloc((strlen(argv[1]) + 50)*sizeof(char));
	char* commande2 = malloc((strlen(argv[1]) + 50)*sizeof(char));
	
	commande1[0] = '\0';
	strcat(commande1,"ls ");
	strcat(commande1,argv[1]);
	
	strcpy(commande2,commande1);
	strcat(commande2," > /dev/null");
	
	pid = fork();
	if(pid == -1)exit(0);
	else if(pid == 0)
	{
		//system(commande1);
		system(commande2);
	}
	else
	{
		wait(&status);
		times(&tmp);
		printf("%f\n",tmp.tms_cutime);
	}
	
	exit(0);
}
