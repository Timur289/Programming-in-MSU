#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>
sem_t sem;
int main(void){
  int val;
  sem_init(&sem, 0, 0);
  sem_getvalue(&sem, &val);
  printf("%d\n", val);
  sem_post(&sem);
  sem_getvalue(&sem, &val);
  printf("%d\n", val);
  sem_wait(&sem);
  sem_getvalue(&sem, &val);
  printf("%d\n", val);
  return 0;
}
