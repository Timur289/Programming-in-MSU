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

void *pisateli_func(void *arg)
{
	int idp;
	idp=*(int *)arg;
	sem_post(&pis);

    while(1)
    {
		pthread_mutex_lock(&sostoyanie);
        if(sos==0)
        {
			sos--;
			pthread_mutex_unlock(&sostoyanie);
			printf("Pisatel %d zashel v biblioteku\n\n",idp);
			sleep(1+rand()%3);
			pthread_mutex_lock(&sostoyanie);
			sos=0;
			pthread_mutex_unlock(&sostoyanie);
			printf("Pisatel %d vishel iz biblioteki.\n",idp);
			sem_post(&pisatel);
			sem_post(&chitatel);
			sleep(rand()%3);
		}
		else
		{
			pthread_mutex_unlock(&sostoyanie);
			printf("Pisatel %d ne mojet zayti v biblioteku.\n",idp);
			sem_wait(&pisatel);
		}
    }
    return NULL;
}
void *chitateli_func(void *arg)
{
	int idc, jduwie_chitateli=0;
	int k=0;
	idc=*(int *)arg;
	sem_post(&chit);

	while(1)
	{
		pthread_mutex_lock(&sostoyanie);
        if(sos>=0)
        {
			sos++;
			pthread_mutex_unlock(&sostoyanie);
			printf("Chitatel %d zashel v biblioteku.\n",idc);
			if(jduwie_chitateli==1)
			{
				sem_post(&chitatel);
				jduwie_chitateli=0;
			}
			sleep(rand()%3);
			pthread_mutex_lock(&sostoyanie);
			sos--;
			pthread_mutex_unlock(&sostoyanie);

			if(idc==1)
			{
				 k++;
				 printf("Perviy Chitatel vishel.__________\n");
			}
			else
			{
				printf("Chitatel %d vishel iz biblioteki\n",idc);
			}
			if(k==3)
			{
				printf ("~~~~~~~~~~~~~~~~~\n");
				break;
			}
			pthread_mutex_lock(&sostoyanie);
			if(sos==0)
			{
				sem_post(&pisatel);
			}
			pthread_mutex_unlock(&sostoyanie);
			sleep(rand()%3+4);
		}
		else
		{
			pthread_mutex_unlock(&sostoyanie);
			printf("Chitatel %d ne mojet zayti v biblioteku\n",idc);
			sem_wait(&chitatel);
			jduwie_chitateli=1;
		}
	}
	return NULL;
}

int main(void)
{
	int id, result1, result2;
	pthread_t chitateli[50], pisateli[5];
	sem_init(&pisatel,0,0);
	sem_init(&chitatel,0,0);
	sem_init(&chit,0,0);
	sem_init(&pis,0,0);

	for(id=1; id<51; id++)
	{
		result1=pthread_create(&chitateli[id-1],NULL,chitateli_func,&id);
		if(result1!=0)
		{
			printf("Chitatel %d умер v зародыше\n", id);
			return EXIT_FAILURE;
		}
	//	else printf("Chitatel %d появился на свет\n", id);
		sem_wait(&chit);
	}

	for(id=1; id<6; id++)
	{
		result2=pthread_create(&pisateli[id-1],NULL,pisateli_func,&id);
		if(result2!=0)
		{
			printf("Pisatel %d умер v зародыше\n", id);
			return EXIT_FAILURE;
		}
	//	else printf("Pisatel %d появился на свет\n", id);
		sem_wait(&pis);
	}

	for(id=1; id<51; id++)
	{
		result1=pthread_join(chitateli[0],NULL);
		if(result1!=0)
		{
			printf("Chitatel %d играет v прятки", id);
			return EXIT_FAILURE;
		}
	//	else printf("Вижу читателя %d \n", id);
		return 0;
	}

	for(id=1; id<6; id++)
	{
		result2=pthread_join(pisateli[id-1],NULL);
		if(result2!=0)
		{
			printf("Pisatel %d играет v прятки", id);
			return EXIT_FAILURE;
		}
		//else printf("Вижу писателя %d\n", id);
	}
    return EXIT_SUCCESS;
}
