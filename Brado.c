#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N 10
sem_t sem;
sem_t divan;
sem_t salon;
pthread_mutex_t kreslo;

void *bradobrey(void *);
void *posetitel(void *);

int main(void) {
	int i, res;
	pthread_t bradobr;
  pthread_t klientm[N];
	sem_init(&sem,0,0);
	sem_init(&divan,0,5);
  sem_init(&salon,0,2);
	pthread_mutex_init(&kreslo,0);

  res = pthread_create(&bradobr,0,bradobrey,0);
  if (res) EXIT_FAILURE;
  else printf("Bradobrey priwel\n\n");
  sem_wait(&sem);
  for(i = 0; i < N; i++) {
    res = pthread_create(&posetitel,0,klientm[i],0);
    if(res) EXIT_FAILURE;
    else printf("Posetitel %d priwel\n\n", i+1);
    sem_wait(&sem);
  }

  pthread_mutex_destroy(&kreslo);
  sem_destroy(&sem);
  sem_destroy(&divan);
  sem_destroy(&salon);
	return EXIT_SUCCESS;
}

void *bradobrey(void *arg) {
	int loc_id = *(int *)arg;
	sem_post(&sem);
  while(1){


  }

	return NULL;
}

void *posetitel(void *arg) {
	int loc_id = *(int *)arg;
	sem_post(&sem);
  while(1){
    sem_wait(&salon);
    sem_wait(&divan);

  }

	return NULL;
}
