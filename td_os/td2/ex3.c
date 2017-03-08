#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <math.h>

#define nbr_process 3
#define nbr_niveau 3

int generer(int niveau);

//~ int main(int argc, char** argv)
//~ {
	//~ int niveau = 1;
	//~ int pid;
	//~ int return_value;
	//~ int i;
	
	//~ niveau_suivant:
	
	//~ for(i=1;i<=nbr_process;i++)
	//~ {
		//~ pid = fork();
		//~ if(pid == -1)exit(0);
		//~ if(pid == 0)
		//~ {
			//~ if(niveau<nbr_niveau)
			//~ {
				//~ niveau++;
				//~ goto niveau_suivant;
			//~ }
			//~ else break;
		//~ }
	//~ }
	
	
	
	//~ if(pid == 0)
	//~ {
		//~ exit(getpid() % 10);
	//~ }
	
	//~ else
	//~ {
		//~ for(i=0;i<nbr_process;i++)
		//~ {
			//~ pid = wait(&return_value);
			
			//~ printf("pid fils : %d\n",pid);
			//~ printf("return_value : %d\n",WEXITSTATUS(return_value));
		//~ }
	//~ }
	
	//~ exit(0);
//~ }

int main(int argc, char** argv)
{
	generer(1);
}

int generer(int niveau)
{
	int pid;
	int return_value;
	int i;
	
	for(i=1;i<=nbr_process;i++)
	{
		pid = fork();
		if(pid == -1)exit(0);
		if(pid == 0)
		{
			if(niveau<nbr_niveau)
			{
				generer(niveau+1);
				break;
			}
			else exit(0);
		}
	}
	
	for(i=0;i<nbr_process;i++)
	{
		pid = wait(&return_value);
		
		printf("pid fils : %d\n",pid);
		//printf("return_value : %d\n",WEXITSTATUS(return_value));
	}
	
	exit(0);
}
