#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

static void sig_usr(int signo) {
	if(signo == SIGUSR1)
		printf("SIGUSR1 recieved from its cihld\n");
	else if (signo == SIGUSR2)
		printf("SIGUSR2 received from its child\n");
}

/* 자식 프로세스 */
int main(void){
	if (!fork() ){
		int ppid;

		ppid = getppid();
		kill(ppid, SIGUSR1);
		kill(ppid, SIGUSR2);
		kill(ppid, SIGINT);

		exit(0);
	}

	/* 부모 프로세스 */
	else{
		/* signal handler registaration*/
	if (signal ( SIGUSR1 , sig_usr ) == SIG_ERR )
		perror ( " can ’ t catch SIGUSR1" ) ;
	if (signal ( SIGUSR2 , sig_usr ) == SIG_ERR )
		perror ( " can ’ t catch SIGUSR2" ) ;

	//if(signal (SIGINT, sig_usr) == SIG_ERR)
		//perror("cannot catch SIGNIT\n");

	/* 자식 프로세스의 종료를 기다리기*/
	wait(NULL);

	}

	return 0;
}



