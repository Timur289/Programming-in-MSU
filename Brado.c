#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem;
sem_t divan;
pthread_mutex_t brado;


int main(void) {
	int i, res;
	pthread_t ;
	sem_init(&sem,0,0);
	sem_init(&divan,0,0);
	pthread_mutex_init(&brado,0);
	return EXIT_SUCCESS;
}

void *bradobrey(void *arg) {
	int loc_id = *(int *)arg;
	
	return NULL;
}

void *posetitel(void *arg) {
	int loc_id = *(int *)arg;
	
	return NULL;
}
