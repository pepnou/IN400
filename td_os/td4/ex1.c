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

void* barrier(void* a)
{
	pthread_mutex_lock(&mutex);
	twait++;
	if(twait<nthreads) pthread_cond_wait(&cond,&mutex);
	else pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
	
	return NULL;
}

void* thread(void* a)
{
	sleep(rand()%10+1);
	
	barrier(NULL);
	
	return NULL;
}

int main()
{
	srand(time(NULL));
	
	int i;
	pthread_t tid[nthreads];
	
	for(i=0;i<nthreads;i++)
	{
		pthread_create(&tid[i],NULL,barrier,NULL);
	}
	
	for(i=0;i<nthreads;i++)
	{
		pthread_join(tid[i],NULL);
	}
	
	exit(EXIT_SUCCESS);
} 
