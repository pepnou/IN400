#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define nbr_case 20
#define nbr_thread 5
typedef struct
{
	int deb,fin,max;
	int* tab;
	
}donnees;

void* max(void* arg)
{
	donnees* a = (donnees*)arg;
	int i;
	
	for(i = a -> deb;i < a -> fin;i++)
		if(a->tab[i] > a->max)a->max = a->tab[i];
	
	return NULL;
}

int main()
{
	srand(time(NULL));
	
	pthread_t tid[nbr_thread];
	donnees info[nbr_thread];
	int alea[nbr_case],i,res = 0;
	
	for(i=0;i<nbr_case;i++)
	{
		alea[i]=rand()%1000 + 1;
		//printf("%d\n",alea[i]);
	}
	
	for(i=0;i<nbr_thread;i++)
	{
		info[i].deb = i * nbr_case / nbr_thread;
		info[i].fin = (i + 1 ) * nbr_case / nbr_thread;
		info[i].max = 0;
		info[i].tab = alea;
		
		//printf("deb : %d ; fin : %d ;\n",info[i].deb,info[i].fin);
		
		pthread_create(&tid[i],NULL,max,&info[i]);
	}
	
	for(i=0;i<nbr_thread;i++) pthread_join(tid[i],NULL);
	
	for(i=0;i<nbr_thread;i++)
	{
		if(info[i].max > res) res = info[i].max;
	}
	
	//printf("max : %d\n",res);
	
	return 0;
}
