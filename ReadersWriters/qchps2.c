#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define N 40
#define M 10
#define READERS_PREFERENCE 1
#define WRITERS_PREFERENCE 0
sem_t pisatel, sem, chitatel;
pthread_mutex_t database;
int sost = 0, prior = WRITERS_PREFERENCE;
double ojidaniyeC = 0, ojidaniyeP = 0;
int c[N], p[M];

void *pisateli(void *);
void *chitateli(void *);
void *dispetcher(void *);

int main(void) {
  int i, res;
  pthread_t ch[N], ps[M], dis;
  sem_init(&pisatel,0,0);
  sem_init(&chitatel,0,0);
  sem_init(&sem,0,0);
  pthread_mutex_init(&database,0);
  for(i = 0; i < N; i++) c[i] = 0;
  for(i = 0; i < M; i++) p[i] = 0;
  res = pthread_create(&dis, NULL, dispetcher, NULL);
  if(res) return EXIT_FAILURE;
  else printf("Dispetcher zapushen\n");

  for(i = 0; i < N; i++) {
    res = pthread_create(&ch[i], NULL, chitateli, &i);
    if(res) return EXIT_FAILURE;
    else printf("Chitatel %d perviy raz zawel v biblioteku\n\n", i + 1);
    sem_wait(&sem);
  }

  for(i = 0; i < M; i++) {
      res = pthread_create(&ps[i], NULL, pisateli, &i);
      if(res) return EXIT_FAILURE;
      else printf("Pisatel %d perviy raz zawel v biblioteku\n\n", i + 1);
      sem_wait(&sem);
  }

  sleep(20);

  for(i = 0; i < N; i++) printf("Chitatel %d bil v biblioteke %d raz\n\n", i+1, c[i]);
  for(i = 0; i < M; i++) printf("Pisatel %d bil v biblioteke %d raz\n\n", i+1, p[i]);

  sem_destroy(&sem);
  sem_destroy(&chitatel);
  sem_destroy(&pisatel);
  pthread_mutex_destroy(&database);

  return EXIT_SUCCESS;
}

void *dispetcher(void *arg){
  while(1) {
//  printf("C: %0.2lf\t P: %0.2lf\n\n", ojidaniyeC, ojidaniyeP);
	 if(ojidaniyeC/N > ojidaniyeP/M) {
	   prior = READERS_PREFERENCE;
	 }
	 else {
	   prior = WRITERS_PREFERENCE;
	 }
    //sleep(2)
  }
  return NULL;
}

void *pisateli(void *arg) {
  int loc_id = *(int *)arg;
  sem_post(&sem);
  while(1) {
	  pthread_mutex_lock(&database);
    if(!sost) {
  		sost--;
    	printf("Pisatel %d zashel v biblioteku\n\n", loc_id + 1);
  		pthread_mutex_unlock(&database);
  		p[loc_id]++;
  	//	sleep(rand()%3);
    //  if(prior == READERS_PREFERENCE) sleep(4);
    //  else sleep(2);
  		pthread_mutex_lock(&database);
  		sost = 0;
  		pthread_mutex_unlock(&database);
  	//	printf("Pisatel %d vishel iz biblioteki.\n\n", loc_id + 1);
      if(prior == READERS_PREFERENCE) {
        sem_post(&chitatel);
        sem_post(&pisatel);
      //  sleep(3);
      }
      else {
        sem_post(&chitatel);
        sem_post(&pisatel);
      //  sleep(2);
    		//sleep(rand()%3);
    	}
    }
  	else {
      ojidaniyeP++;
  		pthread_mutex_unlock(&database);
  	//	printf("Pisatel %d ne mojet zayti v biblioteku.\n\n", loc_id + 1);
  		sem_wait(&pisatel);
  		pthread_mutex_lock(&database);
  		ojidaniyeP--;
  		pthread_mutex_unlock(&database);
      }
    }
  return NULL;
}

void *chitateli(void *arg) {
	int loc_id = *(int *)arg, ojid = 0;
	sem_post(&sem);
	while(1) {
		pthread_mutex_lock(&database);
		if(sost >= 0) {
      if(ojidaniyeP == 0 || prior != WRITERS_PREFERENCE) {
      			sost++;
      			pthread_mutex_unlock(&database);
            c[loc_id]++;
      		//	printf("Chitatel %d zashel v biblioteku.\n\n", loc_id + 1);
    			  if(ojid) { sem_post(&chitatel); ojid = 0;}
    		//	sleep(rand()%3);
        //    if(prior == READERS_PREFERENCE) sleep(1.2);
            //else  sleep(2);
    			pthread_mutex_lock(&database);
    			sost--;
    			if(!sost) sem_post(&pisatel);
    		//	printf("Chiatatel %d vishel iz biblioteki.\n\n", loc_id + 1);
    			pthread_mutex_unlock(&database);
    		 //	sleep(rand()%3);
        // if(prior == READERS_PREFERENCE) sleep(0.5);
 				// else sleep(2);
      }
      else {goto here;}
		}
		else {
      here:
      ojidaniyeC++;
			pthread_mutex_unlock(&database);
      ojid = 1;
		//	printf("Chitatel %d ne mojet zayti v biblioteku\n\n", loc_id + 1);
			sem_wait(&chitatel);
      pthread_mutex_lock(&database);
			ojidaniyeC--;
      pthread_mutex_unlock(&database);
		}
	}
	return NULL;
}
