#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

int nthreads = 50;
int twait = 0;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* barrier(void* a)
{
	pthread_mutex_lock(&mutex);
	twait++;
	if(twait<nthreads) pthread_cond_wait(&cond,&mutex);
	else pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

void* threadA(void* a)
{
	pthread_mutex_lock(&mutex2);
	int temps = rand()%10+1;
	pthread_mutex_unlock(&mutex2);
	
	sleep(temps);
	
	barrier(NULL);
	
	return NULL;
}

int main()
{
	srand(time(NULL));
	
	int i;
	pthread_t tid[nthreads-1];
	
	for(i=0;i<nthreads-1;i++)
	{
		pthread_create(&tid[i],NULL,barrier,NULL);
	}
	
	for(i=0;i<nthreads-1;i++)
	{
		pthread_join(tid[i],NULL);
	}
	
	barrier(NULL);
	
	exit(EXIT_SUCCESS);
} 
