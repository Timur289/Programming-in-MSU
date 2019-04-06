#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N 20

int n = 0;
sem_t sem;
sem_t divan;
sem_t zal;
sem_t kreslo;
sem_t brad;
sem_t rabota;
//pthread_mutex_t strijka;

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
	sem_init(&rabota,0,0);
	//pthread_mutex_init(&strijka,0);

  res = pthread_create(&bradobr,0,bradobrey,0);
  if (res) return EXIT_FAILURE;
  else printf("Bradobrey priwel\n\n");
  for(i = 0; i < N; i++) {
    res = pthread_create(&klientm[i],0,posetitel,&i);
    if(res) return EXIT_FAILURE;
//    else printf("Posetitel %d priwel\n\n", i+1);
//    sleep(rand()%3+1);
    sem_wait(&sem);
  }

  for(i = 0; i < N; i++){
    res = pthread_join(klientm[i],0);
    if(res) return EXIT_FAILURE;
//    else printf("Klient %d ushel\n\n", i + 1);
  }
  
  //pthread_mutex_destroy(&strijka);
  sem_destroy(&sem);
  sem_destroy(&zal);
  sem_destroy(&kreslo);
  sem_destroy(&brad);
  sem_destroy(&divan);
  sem_destroy(&rabota);
  return EXIT_SUCCESS;
}

void *bradobrey(void *arg) {
  while(1){
    sem_wait(&brad);
    //sleep(0.5);
    //pthread_mutex_unlock(&strijka);
    sem_post(&rabota); //можно уходить

  }
	return NULL;
}

void *posetitel(void *arg) {
	int loc_id = *(int *)arg;
	sem_post(&sem);
/*	if(n >= 10) {
		printf("Klient %i ushel tak kak net mesta\n\n", loc_id + 1);
		return NULL;
	}

	else 	*/{
		sem_wait(&zal);
		n++;
		sem_wait(&divan);
		sem_post(&zal);
		n--;
		sem_wait(&kreslo);
		sem_post(&divan);
		sem_post(&brad);
		//pthread_mutex_lock(&strijka);
		sem_wait(&rabota); //ждать пока дадут уйти
		sem_post(&kreslo);
    printf("Klient postrijen %d\n",loc_id+1);		
		return NULL;
	}
	
}
