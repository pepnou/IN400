#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 20

void* double_(void* d)
{
	int i = *((int*)d);
	int* j = malloc(sizeof(int));
	
	*j = i;
	
	printf("thread : %d\n",*j);
	
	*j = 2*i;
	
	return j;
}

int main()
{
	pthread_t tid[N];
	
	int i;
	int tab[N];
	int tmp;
	void* tmp2;
	
	
	
	for(i=0;i<N;i++)
	{
		tab[i]=i;
		 pthread_create(&tid[i],NULL,double_,&tab[i]);
	}
	
	for(i=0;i<N;i++)
	{
		pthread_join(tid[i],&tmp2);
		tmp = *((int*)tmp2);
		printf("retour : %d\n",tmp);
	}
	
	exit(0);
}
