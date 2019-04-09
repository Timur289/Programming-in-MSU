#include <unistd.h>
#include <stdio.h>
int main (void) {
	char *arg[] = { "/usr/bin/ls", 0 };

	if (fork() == 0) {
		printf("In child process:\n");
		execv(arg[0], arg);
		printf("I will never be called\n");
	}
	printf("Execution continues in parent process\n");
}
