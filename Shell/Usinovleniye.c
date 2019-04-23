#include <unistd.h>
#include <stdio.h>
int main(void) {
	int i;
	if (fork()) {
		sleep(2);
		_exit(0);
	}
	for (i=0; i < 5; i++) {
		printf("My parent is %d\n", getppid());
		sleep(1);
	}
}
