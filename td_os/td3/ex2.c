#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define nbr_case 20
#define nbr_thread 15
typedef struct
{
	int deb,fin,max;
}donnees;

void* max(

int main()
{
	srand(time(NULL));
	
	pthread_t tid[nbr_thread];
	donnees info[nbr_thread];
	int alea[nbr_case],i;
	
	for(i=0;i<nbr_case;i++)alea[i]=rand()%1000 + 1;
	
	
	
	return 0;
}
