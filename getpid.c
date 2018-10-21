#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
	printf("hello, world from process %d/n", getpid());
	exit(EXIT_SUCCESS);
}
	
