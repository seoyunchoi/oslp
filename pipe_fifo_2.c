#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#define FIFO_NAME "FIFO_FD"

int main(void){
	char buf[100];
	int num, fd;

	/* FIFO에 사용할 파일 지시자 생성 */
	if( mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
		perror("mknod error");
	}

	/* FIFO를 통해 데이터 전송 받을 상대측 프롯세스를 기다림 */
	/* 상대 측 프로세스가 FIFO 파일 지시자를 열면, 우리도 연다 */
	printf("Reader: waiting for a reader.\n");
	fd = open(FIFO_NAME, O_RDONLY);

	printf("Reader: the writer ready.\n");

	/* 루프를 돌면서 FIFO를 통해 상대측이 전달한 데이터를 읽어들임 */
	do{
		if ((num = read(fd, buf, 100)) == -1)
			perror ("read error");
		else{
			buf[num] = '\0';
			printf("Reader: %d bytes read: %s", num, buf);
		}
		} while(num>0);

		return 0;

	}
