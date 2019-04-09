#include <unistd.h>
#include <stdio.h>


int main (void) {
	pid_t p;
	p = fork();
	printf("fork returned %d\n", p);
}
