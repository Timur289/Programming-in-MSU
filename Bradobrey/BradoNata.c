#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/times.h>
sem_t vidacha_nomerov;
sem_t prixojaya;
sem_t divan;
sem_t kreslo;
sem_t otdix_bradobreya;
sem_t EXIT;

void *bradobrey_f(void *arg)
{
    while(1)
    {
        sem_wait(&otdix_bradobreya);                                    // Ждёт пока кто-то сядет.
        sleep(1);                                                        // Стрижёт.
        sem_post(&EXIT);
    }
}


void *client_f(void *arg)
{   
    int id = *(int*)arg;                       
    sem_post(&vidacha_nomerov);                                            // клиент взял номер
    sem_wait(&prixojaya);                                                // зашёл в прихожую
    sleep(1);                                                           
    sem_wait(&divan);                                                    // уселся на диван
    sem_post(&prixojaya);                                                // => вышел из прихожей
    sleep(1);                                                           
    sem_wait(&kreslo);                                                    // уселся в кресло
    sem_post(&divan);                                                    // диван освободили
    sem_post(&otdix_bradobreya);                                        // "спит"                           
    sem_wait(&EXIT);                                                    // EXIT
    printf("Kliyenta %d postrigli\n", id);
    sem_post(&kreslo);                                                    // освободили кресло
    return NULL;
}


int main()
{
   
    pthread_t bradobrey, client[10];
    int i, res;
   
    sem_init(&vidacha_nomerov, 0, 0);
    sem_init(&prixojaya, 0, 10);
    sem_init(&divan, 0, 5);
    sem_init(&kreslo, 0, 1);
    sem_init(&otdix_bradobreya, 0, 0);
    sem_init(&EXIT, 0, 0);
   
    res = pthread_create(&bradobrey, NULL, &bradobrey_f, &i);
    if(res)
        {
            printf("Bradobrey ne prishel");
            return     EXIT_FAILURE;
        }
    else printf("Bradobrey prishel \n");
   
    for(i = 1; i <= 10; i++)
     {
        res = pthread_create(&client[i-1], NULL, &client_f, &i);
        if(res)
        {
            printf("Klient %d ne prishel", i);
            return     EXIT_FAILURE;
        }
        else printf("Klient %d prishel \n", i);
        sem_wait(&vidacha_nomerov);
     }
   
    for (i = 0; i < 10; i++) pthread_join(client[i], NULL);

    sem_destroy(&vidacha_nomerov);
    sem_destroy(&prixojaya);
    sem_destroy(&divan);
    sem_destroy(&kreslo);
    sem_destroy(&otdix_bradobreya);
    sem_destroy(&EXIT);
   
    return EXIT_SUCCESS;
}

