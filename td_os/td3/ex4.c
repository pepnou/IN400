#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nbr_case 20
#define nbr_consomateur 10
#define nbr_producteur 10
#define iterations 20

sem_t case_vide ;
sem_t case_pleine ;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int var1=0,var2=0;

int T[nbr_case];

void* producteur(void* d)
{
	int m;int i;
	for(i=0;i<iterations;i++)
	{
		m = rand() % 1000 + 1;
		
		sem_wait(&case_vide);
		pthread_mutex_lock(&mutex1);
		T[var1] = m;
		var1 = (var1 + 1) %  nbr_case;
		pthread_mutex_unlock(&mutex1);
		sem_post(&case_pleine);
	}
	
	return NULL;
}

void* consommateur(void* d)
{
	int m;int i;
	for(i=0;i<iterations;i++)
	{
		sem_wait(&case_pleine);
		pthread_mutex_lock(&mutex2);
		m = T[var2];
		printf("%d\n",m);
		var2 = (var2 + 1) %  nbr_case;
		pthread_mutex_unlock(&mutex2);
		sem_post(&case_vide);
	}
	
	return NULL;
}

int main()
{
	srand(time(NULL));
	
	sem_init(&case_vide,0,nbr_case);
	sem_init(&case_pleine,0,0);
	
	pthread_t tid[nbr_consomateur + nbr_producteur];
	
	int i;
	for(i=0;i<nbr_producteur;i++)pthread_create(&tid[i],NULL,producteur,NULL);
	for(i=i;i<nbr_consomateur + nbr_producteur;i++)pthread_create(&tid[i],NULL,consommateur,NULL);
	for(i=0;i<nbr_consomateur + nbr_producteur;i++)pthread_join(tid[i],NULL);
	
	return EXIT_SUCCESS;
}
