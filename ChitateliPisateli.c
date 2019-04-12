#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#define N 40
#define M 10
sem_t sem;
sem_t bibliotekorsha;
sem_t database;
sem_t cherniyvxod;
pthread_mutex_t sost;

int sostbibl = 0;
unsigned int n = 0;
unsigned int m = 0;

void *chitatel(void *);
void *pisatel(void *);

int main(void){
  printf("Smth");
  int i, res;
  pthread_t ch[N], ps[M];
  sem_init(&sem,0,0);
  sem_init(&bibliotekorsha,0,1);
  sem_init(&database,0,1);
  sem_init(&cherniyvxod,0,1);
  printf("sldg");
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
  sem_destroy(&bibliotekorsha);
  sem_destroy(&database);
  sem_destroy(&cherniyvxod);
  pthread_mutex_destroy(&sost);

  printf("Done\n\n");
  return EXIT_SUCCESS;
}


void *chitatel(void *arg){
  int id = *(int *)arg;
  int i;
  sem_post(&sem);//запускаем по очереди
  for(i = 0; i < 3; i++) {
	 
    sem_wait(&bibliotekorsha);//просим библиотекоршу оформить пропуск
    n++;
    sem_post(&bibliotekorsha); //библиотекорша дает читателю пропуск и ждет следующего посетителя
    printf("Reader %d is reading\n\n", id + 1);
    sleep(2);
    sem_wait(&bibliotekorsha); //выходим и оформляемся у библиотекорши
    n--;
    sem_post(&bibliotekorsha); //уходим и отпускаем библиотекоршу
    if(n == 0)  sem_post(&database); //последний читатель ушел и открыл библиотеку писателям
    //sleep(15);
  }
  return NULL;
}

void *pisatel(void *arg) {
  int id = *(int *)arg;
  int i;
  sem_post(&sem);
  
  for(i = 0; i < 2; i++){
    sem_wait(&cherniyvxod);//просим библиотекоршу оформить пропуск
    m++;
    if(m == 1) sem_wait(&database); //первый писатель присваевает библиотеку писателям
    sem_post(&cherniyvxod); //библиотекорша дает писателю пропуск и ждет следующего посетителя
    printf("Writer %d is writing\n\n", id + 1);
    sleep(6);
    sem_wait(&cherniyvxod); //выходим к черному входу
    m--;
    sem_post(&cherniyvxod); //уходим через черный вход
    if(m == 0)  sem_post(&database);
  }
  return NULL;
}
