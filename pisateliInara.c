#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t pisatel;
sem_t pis;
sem_t chitatel;
sem_t chit;
static pthread_mutex_t sostoyanie = PTHREAD_MUTEX_INITIALIZER;
int sos=0;
int jduwie_pisateli=0;

void *pisateli_func(void *arg)
{
	int idp, k=0;
	idp=*(int *)arg;
	sem_post(&pis);

    while(1)
    {
		pthread_mutex_lock(&sostoyanie);
        if(sos==0)
        {
			sos--;
			pthread_mutex_unlock(&sostoyanie);
			//printf("Колличество ждущих писателей: %d\n", jduwie_pisateli);
			printf("Писатель %d зашёл в библиотеку.\n",idp);
			sleep(rand()%3+1);
			pthread_mutex_lock(&sostoyanie);
			sos=0;	
			pthread_mutex_unlock(&sostoyanie);
			if(idp==1)
			{
				k++;
				printf("Первый писатель вышел из библиотеки.\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~\n");
			}
			else
			{
				printf("Писатель %d вышел из библиотеки.\n",idp);
			}
			if(k==3) break;
			sem_post(&pisatel);
			sem_post(&chitatel);
			sleep(rand()%3+7);
		}
		else
		{
			jduwie_pisateli++;
			pthread_mutex_unlock(&sostoyanie);	
			printf("Писатель %d не может зайти в библиотеку.\n",idp);
			sem_wait(&pisatel);	
			pthread_mutex_lock(&sostoyanie);	
			jduwie_pisateli--;	
			pthread_mutex_unlock(&sostoyanie);	
			//printf("Колличество ждущих писателей: %d\n", jduwie_pisateli);
		}
    }
    return NULL;
}

void *chitateli_func(void *arg)
{
	int idc, jduwie_chitateli=0;
	idc=*(int *)arg;
	sem_post(&chit);
	
	while(1)
	{
		pthread_mutex_lock(&sostoyanie);
		if(jduwie_pisateli==0 && sos>=0)
		{
			sos++;
			pthread_mutex_unlock(&sostoyanie);
			printf("Читатель %d зашёл в библиотеку.\n\n",idc);
			if(jduwie_chitateli==1)
			{
				sem_post(&chitatel);
				jduwie_chitateli=0;
			}
			sleep(rand()%3);
			pthread_mutex_lock(&sostoyanie);
			sos--;
			printf("Читатель %d вышел из библиотеки.\n",idc);
			if(sos==0)
			{
				sem_post(&pisatel);
			}
			pthread_mutex_unlock(&sostoyanie);
			sleep(rand()%3+1);
		
		}	
		else
		{
			pthread_mutex_unlock(&sostoyanie);
			printf("Читатель %d не может зайти в библиотеку.\n",idc);				
			sem_wait(&chitatel);
			jduwie_chitateli=1;
		}
	}
	return NULL;
}

int main(void)
{
	int id, result1, result2, n, m;
	printf("Введите число читателей:");
	scanf("%d", &n);
	printf("Введите число писателей:");
	scanf("%d", &m);
	pthread_t chitateli[n], pisateli[m];
	sem_init(&pisatel,0,0);
	sem_init(&chitatel,0,0);
	sem_init(&chit,0,0);
	sem_init(&pis,0,0);

	for(id=1; id<(m+1); id++)
	{
		result2=pthread_create(&pisateli[id-1],NULL,pisateli_func,&id);
		if(result2!=0)
		{
			printf("Писатель %d умер в зародыше.\n", id);
			return EXIT_FAILURE;
		}
		//else printf("Писатель %d  появился на свет.\n", id);
		sem_wait(&pis);
	}
	
	for(id=1; id<(n+1); id++)
	{
		result1=pthread_create(&chitateli[id-1],NULL,chitateli_func,&id);
		if(result1!=0)
		{
			printf("Читатель %d умер в зародыше.\n", id);
			return EXIT_FAILURE;
		}
		//else printf("Читатель %d появился на свет.\n", id);
		sem_wait(&chit);
	}
	
	for(id=1; id<(m+1); id++)
	{
		result2=pthread_join(pisateli[0],NULL);
		if(result2!=0)
		{
			printf("Писатель %d играет в прятки.\n", id);
			return EXIT_FAILURE;
		}
		//else printf("Вижу писателя %d\n", id);
		return 0;
	}
	
	for(id=1; id<(n+1); id++)
	{
		result2=pthread_join(chitateli[id-1],NULL);
		if(result2!=0)
		{
			printf("Читатель %d играет в прятки.\n", id);
			return EXIT_FAILURE;
		}
		//else printf("Вижу читателя %d\n", id);
	}
    return EXIT_SUCCESS;
}
