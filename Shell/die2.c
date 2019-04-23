#include <unistd.h>
#include <stdio.h>
int main(void) {
	if (!fork()) {
		_exit(0);
	}
	sleep(60);
}
