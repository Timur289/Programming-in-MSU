#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>

sem_t fdoor;
sem_t sdoor;
sem_t number;
pthread_mutex_t room;
int n=0;
int max=50;

void *soldier_func(void *arg) {
	int loc_id, i;
	loc_id=*(int*)arg;
	sem_post(&number);
	while(1) {
		pthread_mutex_lock(&room);
		n++;
	    if(n == max) {
			printf("\x1B[31mПоследний %i офицер запускает всех в комнату смерти\n\n", loc_id +1);
			for(i = 0; i < max; i++) sem_post(&fdoor);
            n = 0;
		}
		pthread_mutex_unlock(&room);
		sem_wait(&fdoor);
		sleep(2);
		if(rand()%5 == 0) {
			printf("Офицер %d умер\n\n", loc_id + 1);
			pthread_mutex_lock(&room);
			max--;
			if(n==max) {
				for(i = 0; i < max; i++) sem_post(&sdoor);
				n = 0;
			}
            pthread_mutex_unlock(&room);
            return NULL;
		}
		printf("\033[22;34mОфицер %d выжил\033[0m\n\n", loc_id + 1);
		pthread_mutex_lock(&room);
		n++;
		if(n == max) {
			printf("\x1B[31mПоследний офицер %i выпускает всех из зала ожидания\n\n", loc_id +1);
			for(i = 0; i < max; i++) sem_post(&sdoor);
            n = 0;
		}
        pthread_mutex_unlock(&room);
        sem_wait(&sdoor);
        if(max == 1) {
			printf("Офицер %d остался один!\n\n", loc_id + 1);
			return NULL;
		}
	}
    return NULL;
}

int main(void)
{
	int id, res;
	pthread_t soldiers[50];
	sem_init(&fdoor, 0, 0);
	sem_init(&sdoor, 0, 0);
	sem_init(&number, 0, 0);
	for(id=0; id<50; id++) {
		res = pthread_create(&soldiers[id], NULL, soldier_func, &id);
		if(res) {
			printf("(!)Офицер %d не пришел(!)\n\n", id);
			return EXIT_FAILURE;
		}
		sem_wait(&number);
	}
	for(id = 0; id < 50; id++) res=pthread_join(soldiers[id], NULL);
	sem_destroy(&fdoor);
	sem_destroy(&sdoor);
	sem_destroy(&number);
	pthread_mutex_destroy(&room);
	return EXIT_SUCCESS;
}
