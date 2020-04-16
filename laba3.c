#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

#define FILE_MODE (S_IRWXO | S_IRWXG | S_IRWXU)
#define FIFO "/tmp/fifo.1"

int main()
{	
	const char* SEMP = "/my_semaphore";	
	sem_t *sem;
	if( (sem=sem_open(SEMP,O_CREAT,0777,0)) == SEM_FAILED){
		perror("sem_open");
		return 0; 
	}
	unlink(FIFO);
	pid_t pid;
	int writefd;
	char str[1024];
	//int idpid=getpid();
	
	if(mkfifo(FIFO,0777)==-1) {
		perror("mkfifo");
	   	return 0;
	}
	
	if((pid=fork())==0){					
	   execl("./project","project",NULL);
	}
	else{	
		if((writefd=open(FIFO,O_WRONLY))==-1) {
			printf("Error");
			return 0;
		}
	}
	printf("Server connected\n");
	while(strcmp(str,"EXIT\n")!=0){
	    fflush(stdin);
	    fgets(str,1024,stdin);
	    write(writefd,str,strlen(str) + 1);
	    printf("\tYour message has been sent successfully\n");
	    sem_wait(sem);
	}
	unlink(FIFO);
	return 0;
}

