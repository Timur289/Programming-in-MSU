#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>
sem_t sem;
void *thread_func(void *arg) {
  int i;
  int loc_id = *(int *)arg;
  sem_post(&sem);
  for(i = 0; i < 5; i++) {
    printf("Thread %i is running\n", loc_id);
    sleep(1);
  }
  //sem_post(&sem);
  return NULL;
}

int main(void){
  int id, res;
  pthread_t threadm[3];
  sem_init(&sem, 0, 0);
  for(id = 1; id < 4; id++){
    res = pthread_create(&threadm[id - 1], NULL, thread_func, &id);
    if(res) {
      printf("creating thread %d failed\n", id);
      return EXIT_FAILURE;
    }
    else printf("thread %d created\n", id);
    sem_wait(&sem);
  }


  for(id = 1; id < 4; id++){
    res = pthread_join(threadm[id - 1], NULL);
    if(res) {
      printf("Joining the %d thread failed\n", id);
      return EXIT_FAILURE;
    }
    else printf("%d thread joining\n", id);
  }


  sem_destroy(&sem);
  printf("Done\n");
  return EXIT_SUCCESS;
}
