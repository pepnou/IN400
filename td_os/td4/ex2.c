#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

typedef struct
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	
	int remplie;
	int valeur;
}mailbox;

typedef struct
{
	mailbox* mb1,mb2;
	int m;
	pthread_t tid;
}argument;

void mbox_init(mailbox* mb)
{
	mb -> mutex = PTHREAD_MUTEX_INITIALIZER;
	mb -> cond = PTHREAD_COND_INITIALIZER;
	mb -> remplie = 0;
}

void mbox_write(mailbox* mb, int i)
{
	pthread_mutex_lock(&(mb -> mutex));
	
	if(mb -> remplie != 0) pthread_cond_wait(&(mb -> mutex),&(mb -> cond));
	
	mb -> valeur = i;
	mb -> remplie = 1;
	
	pthread_cond_signal(&(mb -> cond));
	
	pthread_mutex_unlock(&(mb -> mutex));
}

int mbox_read(mailbox* mb)
{
	int res;
	
	pthread_mutex_lock(&(mb -> mutex));
	
	if(mb -> remplie == 0) pthread_cond_wait(&(mb -> mutex),&(mb -> cond));
	
	res = mb -> valeur;
	mb -> remplie = 0;
	
	pthread_cond_signal(&(mb -> cond));
	
	pthread_mutex_unlock(&(mb -> mutex));
	
	return res;
}

int main(int argc, char** argv)
{
	argument arg[argv[1]];
	
	int i;
	
	for(i=0;i<n;i++)
	{
		arg[i].m = argv[2];
		if(i != 0)arg[i].mb1 = arg[i-1].mb2;
		else mbox_init(arg[i].mb1);
		mbox_init(arg[i].mb2);
		
		pthread_create(&(arg[i].tid),NULL,OP_thread,&(arg[i]));
	}
	
	
	
	exit(0);
}

