#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/times.h>

int main(int argc,char** argv)
{
	struct tms yolo;
	
	float temps_d;
	float temps_f;
	
	if(argc == 1)exit(0);
	
	char* commande1 = malloc((strlen(argv[1]) + 50)*sizeof(char));
	char* commande2 = malloc((strlen(argv[1]) + 50)*sizeof(char));
	
	commande1[0] = '\0';
	strcat(commande1,"ls ");
	strcat(commande1,argv[1]);
	
	strcpy(commande2,commande1);
	strcat(commande2," > /dev/null");
	
	times(&yolo);
	
	temps_d = yolo.tms_utime;
	
	system(commande1);
	//system(commande2);
	
	times(&yolo);
	
	temps_f = yolo.tms_utime;
	
	printf("%f\n",temps_f - temps_d);
	
	exit(0);
}
