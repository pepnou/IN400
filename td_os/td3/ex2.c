#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define nbr_case 20

int main()
{
	srand(time(NULL));
	
	int alea[nbr_case],i;
	
	for(i=0;i<nbr_case;i++)alea[i]=rand()%1000 + 1;
	
	
	return 0;
}
