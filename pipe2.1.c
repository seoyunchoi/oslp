#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int i;
int main (void)
{
	int pfd[2];
	char buf[30];

	/* 파이프 생성*/
	if (pipe(pfd) == -1){
		perror("pipe error");
		exit(1);
	}

	if (!fork()) {
		printf("CHILD(PID: %d): Writing to the pipe\n", getpid());

		/* 파이프에 데이터 쓰기 */


		for(i=0; i<10; i++){
		write(pfd[1], "pipe!", 5);
		}

		/* 자식 프로세스 종료*/
		exit(0);
	}

	else {
		printf("PARENT(PID: %d): Reading from the pipe\n", getpid());

		/* 파이프에서 데이터 읽기 */
		// read(pfd[0], buf, 5*i);  //이렇게 하면 초기화 된 i를 계속 0으로 받아들여 buffer를 0만큼 가져옴
		read(pfd[0], buf, 5 * 10);
		printf("PARENT(PID: %d): %s\n", getpid(), buf);

		/* 자식 프로세스의 종료를 기다리기 */
		wait (NULL);
	}

	return 0;
}
