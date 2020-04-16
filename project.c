#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <semaphore.h>

#define SEMP "/my_semaphore"
int main(int argc,char* argv[])
{
	sem_t *sem;
	if((sem=sem_open(SEMP,0))==SEM_FAILED){
	perror("SEM_OPEN");
	return 0;
	}

	int readfd;
	char temp[]="/tmp/fifo.1",  buf[1024];
	readfd=open(temp,O_RDONLY);	
	printf("Client connected\n");
	while (strcmp(buf,"exit\n")!=0){
		read(readfd,buf,sizeof(buf) + 1);
		sem_post(sem);
		printf("\tYour message has been received successfully\n");
		printf("%s",buf);
		fflush(stdin);
	}
	kill(getpid(),SIGINT);
	return 0;
}

