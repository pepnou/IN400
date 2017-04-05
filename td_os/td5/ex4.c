#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

void scribe()
{
	char message[] = "ouiiiiiiiiiiiiiiiiiiii";
	
	mkfifo("pipe_ex4",0644);
	int fd = open("pipe_ex4",O_WRONLY);
	write(fd,message, strlen(message)*sizeof(char));
	close(fd);
}

void lecteur()
{
	char message[1024];
	
	int fd = open("pipe_ex4",O_RDONLY);
	read(fd,message,1024*sizeof(char));
	printf("%s\n",message);
	close(fd);
}

int main(int argc, char** argv)
{
	if(argv[1] == 0)lecteur();
	else scribe();
	
	exit(0);
}
