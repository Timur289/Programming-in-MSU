#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void) {
	int fd_in, fd_out;
	char buf[1024];
	memset(buf, 0, 1024);
	fd_in = open("/tmp/infile", O_RDONLY);
	fd_out = open("/tmp/outfile", O_WRONLY|O_CREAT);
	fork();
	while (read(fd_in, buf, 2) > 0) {
		printf("%d: %s", getpid(), buf);
		sprintf(buf, "%d Hello, world!\n\r", getpid());
		write(fd_out, buf, strlen(buf));
		sleep(1);
		memset(buf, 0, 1024);
	}
	sleep(10);
}
