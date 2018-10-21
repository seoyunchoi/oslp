#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

/* one handler for both signals */
static void sig_usr (int signo) {
	if (signo == SIGUSR1)
	printf("recieved SIGUSR1: %d\n", signo);

	else if (signo == SIGUSR2)
	printf("recieved SIGUSR2: %d\n", signo);
	}

int main(void) {
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	perror("can't catch SIGUSR1");
	
	if(signal(SIGUSR2, sig_usr) == SIG_ERR)
	perror("can't catch SIGURS2");

	for( ; ; )
	sleep(60);
	} 

