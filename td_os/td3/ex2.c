#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define nbr_case 20
#define nbr_thread 15
typedef struct
{
	int deb,fin,max;
	int* tab;
	
}donnees;

void* max(void* arg)
{
	
}

int main()
{
	srand(time(NULL));
	
	pthread_t tid[nbr_thread];
	donnees info[nbr_thread+1];
	int alea[nbr_case],i;
	
	for(i=0;i<nbr_case;i++)alea[i]=rand()%1000 + 1;
	
	for(i=0;i<nbr_thread;i++)
	{
		info[i].deb = i * nbr_case / nbr_thread;
		info[i].fin = (i + 1 ) * nbr_case / nbr_thread;
		info[i].max = 0;
		info[i].tab = alea;
		
		pthread_create(&tid[i],NULL,max,&info[i]);
	}
	
	return 0;
}
