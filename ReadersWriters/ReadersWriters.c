#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <semaphore.h>
#define M 4 //num of WR
#define N 3 //num of RE
int iter = 10; //iteration
sem_t accessM,readresM,orderM; //sem.
unsigned int readers = 0;	// Number of readers accessing the resource

void *reader(void *prm)
{
	int num1=*(int*)prm;
	int i,r;
	for(i=0;i<iter;i++)
	{

		if (sem_wait(&orderM)==0) printf("%d Chitatel %d v ocheredi__________CH%d\n",i,num1,num1);	// Remember our order of arrival
		sem_wait(&readresM);				 // We will manipulate the readers counter
		if (readers == 0)				// If there are currently no readers (we came first)...
			sem_wait(&accessM);				// ...requests exclusive access to the resource for readers
		readers++;							 // Note that there is now one more reader
		sem_post(&orderM);					 // Release order of arrival semaphore (we have been served)
		sem_post(&readresM);				 // We are done accessing the number of readers for now

		printf("%d Rabotaet chitatel %d________________CH%d\n",i,num1,num1);				// Here the reader can read the resource at will
		r=1+rand()%4;
		sleep(r);
		sem_wait(&readresM);				 // We will manipulate the readers counter
		readers--;							 // We are leaving, there is one less reader
		if (readers == 0)				// If there are no more readers currently reading...
			sem_post(&accessM);				// ...release exclusive access to the resource
		sem_post(&readresM);				 // We are done accessing the number of readers for now
	}
  return NULL;
}

void *writer(void *prm)
{
	int num2=*(int*)prm;
	int j,r;
	for(j=0;j<iter;j++)
	{
		if(sem_wait(&orderM)==0) printf("%d pisatel %d v ocheredi__________P%d\n",j,num2,num2); // Remember our order of arrival
		sem_wait(&accessM);					// Request exclusive access to the resource
		sem_post(&orderM);					 // Release order of arrival semaphore (we have been served)

		printf("%d Rabotaet pisatel %d________________P%d\n",j,num2,num2);				 // Here the writer can modify the resource at will
		r=1+rand()%4;
		sleep(r);
		sem_post(&accessM);					// Release exclusive access to the resource
	}
  return NULL;
}

int main(void)
{
	pthread_t threadRE[N];
	pthread_t threadWR[M];
	sem_init(&accessM,0,1);
	sem_init(&readresM,0,1);
	sem_init(&orderM,0,1);

	printf("vvedite iter: ");
	scanf("%d",&iter);
	int i;
	for(i=0;i<M;i++)
	{
		pthread_create(&(threadWR[i]),NULL,writer,(void*)&i);
	}
	for(i=0;i<N;i++)
	{
		pthread_create(&(threadRE[i]),NULL,reader,(void*)&i);
	}


	for(i=0;i<N;i++)
	{
		pthread_join(threadRE[i],NULL);
	}
	for(i=0;i<M;i++)
	{
		pthread_join(threadWR[i],NULL);
	}

	sem_destroy(&accessM);
	sem_destroy(&readresM);
	sem_destroy(&orderM);
  return EXIT_SUCCESS;
}
