#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
void sighandler(int sig) {
	printf("In signal handler for signal %d\n", sig);
	wait(0);
}
int main(void) {
	sigset(SIGCHLD, &sighandler);
	if (!fork()) {
		_exit(0);
	}
	sleep(60);
}
