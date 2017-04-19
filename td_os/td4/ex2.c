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
	mailbox *mb1,*mb2;
	int m;
	pthread_t tid;
}argument;

void mbox_init(mailbox* mb)
{
	//mb -> mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&(mb -> mutex), NULL);
	//mb -> cond = PTHREAD_COND_INITIALIZER;
	pthread_cond_init(&(mb -> cond), NULL);
	mb -> remplie = 0;
}

void mbox_write(mailbox* mb, int i)
{
	pthread_mutex_lock(&(mb -> mutex));
	
	if(mb -> remplie != 0) pthread_cond_wait(&(mb -> cond),&(mb -> mutex));
	
	mb -> valeur = i;
	mb -> remplie = 1;
	
	pthread_cond_signal(&(mb -> cond));
	
	pthread_mutex_unlock(&(mb -> mutex));
}

int mbox_read(mailbox* mb)
{
	int res;
	
	pthread_mutex_lock(&(mb -> mutex));
	
	if(mb -> remplie == 0) pthread_cond_wait(&(mb -> cond),&(mb -> mutex));
	
	res = mb -> valeur;
	mb -> remplie = 0;
	
	pthread_cond_signal(&(mb -> cond));
	
	pthread_mutex_unlock(&(mb -> mutex));
	
	return res;
}

void* OP_thread(void* a)
{
	argument arg = *((argument*)a);
	
	int i;
	
	for(i=0;i<arg.m;i++)
	{
		mbox_write(arg.mb2,mbox_read(arg.mb1)+1);
	}
	
	return NULL;
}

int main(int argc, char** argv)
{
	int n = (int)argv[1];
	int m = (int)argv[2];
	
	argument arg[n];
	
	int i;
	
	for(i=0;i<n;i++)
	{
		arg[i].m = m;
		if(i != 0)arg[i].mb1 = arg[i-1].mb2;
		else mbox_init(arg[i].mb1);
		mbox_init(arg[i].mb2);
		
		pthread_create(&(arg[i].tid),NULL,OP_thread,&(arg[i]));
	}
	
	for(i=0;i<m;i++)
	{
		mbox_write(arg[0].mb1,i);
		printf("%d\n",mbox_read(arg[n-1].mb2));
	}
	
	for(i=0;i<n;i++)
	{
		pthread_join(arg[i].tid,NULL);
	}
	
	exit(0);
}



