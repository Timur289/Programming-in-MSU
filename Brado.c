#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N 10

int n = 0;
sem_t sem;
sem_t divan;
sem_t zal;
sem_t kreslo;
sem_t brad;
pthread_mutex_t strijka;

void *bradobrey(void *);
void *posetitel(void *);

int main(void) {
	int i, res;
	pthread_t bradobr;
	pthread_t klientm[N];
	sem_init(&sem,0,0);
	sem_init(&divan,0,5);
  sem_init(&zal,0,7);
	sem_init(&kreslo,0,1);
  sem_init(&brad,0,0);
  pthread_mutex_init(&strijka,0);

  res = pthread_create(&bradobr,0,bradobrey,0);
  if (res) return EXIT_FAILURE;
  else printf("Bradobrey priwel\n\n");
  for(i = 0; i < N; i++) {
    res = pthread_create(&klientm[i],0,posetitel,&i);
    if(res) return EXIT_FAILURE;
    else printf("Posetitel %d priwel\n\n", i+1);
    sem_wait(&sem);
  }

  for(i = 0; i < N; i++){
    res = pthread_join(klientm[i],0);
    if(res) return EXIT_FAILURE;
    else printf("Klienta %d postrigli\n\n", i + 1);
  }
  pthread_mutex_destroy(&strijka);
  sem_destroy(&sem);
  sem_destroy(&zal);
  sem_destroy(&kreslo);
  sem_destroy(&brad);
  sem_destroy(&divan);
	return EXIT_SUCCESS;
}

void *bradobrey(void *arg) {
//	int loc_id = *(int *)arg;
  while(1){
    sem_wait(&brad);
    sleep(10);
    pthread_mutex_unlock(&strijka);
  }
	return NULL;
}

void *posetitel(void *arg) {
	int loc_id = *(int *)arg;
	sem_post(&sem);
  sem_wait(&zal);
  sem_wait(&divan);
  sem_post(&zal);
  sem_wait(&kreslo);
  sem_post(&divan);
  sem_post(&brad);
  pthread_mutex_lock(&strijka);
  printf("Klient %i strijetsa\n\n", loc_id + 1);
  sem_post(&kreslo);
	return NULL;
}
