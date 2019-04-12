#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#define N 40
#define M 10
sem_t sem;
sem_t bibl;
sem_t database;
sem_t pis;
pthread_mutex_t sost;

int sostbibl = 0;
unsigned int n = 0;
unsigned int m = 0;

void *chitatel(void *);
void *pisatel(void *);

int main(void){
  int i, res;
  pthread_t ch[N], ps[M];
  sem_init(&sem,0,0);
  sem_init(&bibl,0,0);
  sem_init(&database,0,1);
  sem_init(&pis,0,1);
  for(i = 0; i < N; i++){
    res = pthread_create(&ch[i], NULL, chitatel, &i);
    if(res) return EXIT_FAILURE;
    else printf("Chitatel %d perviy raz zawel v biblioteku\n\n", i + 1);
    sem_wait(&sem);
  }

  for(i = 0; i < M; i++){
      res = pthread_create(&ps[i], NULL, pisatel, &i);
      if(res) return EXIT_FAILURE;
      else printf("Pisatel %d perviy raz zawel v biblioteku\n\n", i + 1);
      sem_wait(&sem);
  }

  for(i = 0; i < N; i++){
    res = pthread_join(ch[i], NULL);
    if(res) return EXIT_FAILURE;
    else printf("Chitatel %d uwel\n\n", i+1);
  }

  for(i = 0; i < M; i++){
      res = pthread_join(ps[i], NULL);
      if(res) return EXIT_FAILURE;
      else printf("Pisatel %d uwel\n\n", i+1);
  }

  sem_destroy(&sem);
  sem_destroy(&bibl);
  sem_destroy(&database);
  sem_destroy(&pis);
  pthread_mutex_destroy(&sost);

  printf("Done\n\n");
  return EXIT_SUCCESS;
}


void *chitatel(void *arg){
  int id = *(int *)arg;
  int i;
  sem_post(&sem);
  for(i = 0; i < 3; i++) {
	pthread_mutex_lock(&sost);
	if(sostbibl >= 0) {
		sostbibl++;
		pthread_mutex_unlock(&sost);
		printf("Reader %d is reading\n\n", id + 1);
		sleep(2);
		pthread_mutex_lock(&sost);
		sostbibl--;
		pthread_mutex_unlock(&sost);
		if(!sostbibl) sem_post(&bibl);
	}
	else {
		printf("Pisatel zanal biblioteku i chitatel jdet\n\n");
		pthread_mutex_unlock(&sost);
	}
  }
  return NULL;
}

void *pisatel(void *arg) {
  int id = *(int *)arg;
  int i;
  sem_post(&sem);
  pthread_mutex_lock(&sost);
  for(i = 0; i < 2; i++){
	if(!sostbibl) {
		sostbibl--;
		pthread_mutex_unlock(&sost);
		sem_wait(&pis);
		printf("Writer %d is writing\n\n", id + 1);
		sleep(6);
		pthread_mutex_lock(&sost);
		sostbibl = 0;
		pthread_mutex_unlock(&sost);
		sem_post(&pis);
	}
	else {
		printf("Pisatel ne mojet zayti v bibl\n\n");
		pthread_mutex_unlock(&sost);
		sem_wait(&bibl);
		sem_post(&bibl);
	}
  }
  return NULL;
}
