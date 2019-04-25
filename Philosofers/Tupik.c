#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>
sem_t sem;
sem_t vilka;
void *func(void *arg){
  int loc_id = *(int *)arg;
  sem_post(&sem);
  sem_wait(&vilka);
  printf("\nFilosof %i vzal levuyu vilku\n", loc_id);
  sleep(1);
  sem_wait(&vilka);
  printf("\nFilosof %i vzal pravuyu vilku\n", loc_id);
  sleep(1);
  sem_post(&vilka); sem_post(&vilka);
  //sem_post(&sem);
  printf("Filosof poel\n");
  return NULL;
}

int main(void){
  int id, res, j = 0;
  pthread_t filosm[5];
  sem_init(&sem, 0, 0);
  sem_init(&vilka, 0, 5);
  for(id = 1; id < 6; id++){
    res = pthread_create(&filosm[id - 1], NULL, func, &id);
    if(res) {
      printf("creating thread %d failed\n", id);
      return EXIT_FAILURE;
    }
    sem_wait(&sem);
    //else printf("\nFilosof %d rewil vzat vilku\n", id);
  }
 while(j<10){
   sleep(1);
   j++;
 }
 if(j == 10) exit(0);
  for(id = 1; id < 4; id++){
    res = pthread_join(filosm[id - 1], NULL);
    if(res) {
      printf("Joining the %d thread failed\n", id);
      return EXIT_FAILURE;
    }
    else printf("%d thread joining\n", id);
  }

  return 0;
}
