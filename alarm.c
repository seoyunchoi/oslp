#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>

void clock_tick (int signo) {
	printf("\r%ld", time(NULL));
	alarm(1);
}

void handler_init(int signo) {
}

int main (void) {
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	printf("\e[2J\e[H");

	if (signal(SIGALRM, clock_tick) == SIG_ERR)
		perror("can't catch SIGALARM");

	if (signal(SIGINT, clock_tick) == SIG_ERR)
		perror ("can't catch SIGARLM");
	
	clock_tick(-1);

	for( ; ;)
		pause();

	return(0);
}
		
