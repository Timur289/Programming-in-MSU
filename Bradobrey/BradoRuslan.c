#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

pthread_mutex_t process;
sem_t sem;
sem_t sofa;
sem_t take_armchair;
sem_t barber;
sem_t hall;

void *fbarber(void *arg)
{
	while(true)
	{
		sem_wait(&barber); // Брадобрей блокируется на семафоре, т.к. клиентов нет
		sleep(1);
		pthread_mutex_unlock(&process); // Брадобрей отпускает клиента, клиент выходит
	}
	return NULL;
}

void *fclient(void *arg)
{
	int id=*(int*)arg;
	sem_post(&sem);
	sem_wait(&hall); //Ожидаем место в зале
	//printf("Client %d wait in hall \n\n", id);
	sem_wait(&sofa); // Ожидает место на диване
	//printf("Client %d take place in sofa \n\n", id);
	sem_post(&hall); // Прошли в зал
	//printf("Client %d free place in hall \n\n", id);
	sem_wait(&take_armchair); // Попытка захвата кресла
	sem_post(&barber); // Сообщение для того, чтобы брадобрей проснулся
	sem_post(&sofa); // Место на диване свободно, он его занял
	//printf("Client %d free sofa \n\n", id);
	pthread_mutex_lock(&process);
	printf("Client %d is trimmed \n\n", id);
	sem_post(&take_armchair); // Клиент освободил кресло
	return NULL;
}

int main(void)
{
	int loc_id, p;
	pthread_t barberr, clients[13];
	sem_init(&sem,0,0);
	sem_init(&sofa,0,5);
	sem_init(&take_armchair,0,1);
	sem_init(&hall,0,8);
	sem_init(&barber,0,0);
	p=pthread_create(&barberr, NULL, &fbarber, &loc_id);
	for(loc_id=0; loc_id<13; loc_id++)
	{
		p=pthread_create(&clients[loc_id], NULL, &fclient, &loc_id);
		if(p)
		{
			printf(" --- Client %d did not arrive...", loc_id);
			return 	EXIT_FAILURE;
		}
		sem_wait(&sem);
	}
	for(loc_id=0; loc_id<13; loc_id++)
	{
		p=pthread_join(clients[loc_id], NULL);
		if(p)
		{
			printf(" --- Client %d did not arrive...", loc_id);
			return 	EXIT_FAILURE;
		}
	}
	sem_destroy(&hall);
	sem_destroy(&sofa);
	sem_destroy(&take_armchair);
	sem_destroy(&barber);
	pthread_mutex_destroy(&process);
	return EXIT_SUCCESS;
}
