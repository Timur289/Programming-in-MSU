#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define N 5

sem_t sem;
sem_t podmig;
pthread_mutex_t vilka[N];
int golod[N];
int j;

void *fil(void *);
void *objor(void *);

int main(void){
    int i, res;
    j = 0;
    for(i = 0; i < N; i++) golod[i] = 0;
    pthread_t film[N];
    sem_init(&sem,0,0);
    sem_init(&podmig,0,0);
    for(i = 0; i < N; i++) pthread_mutex_init(&vilka[i],0);
    for(i = 0; i < N; i++){
        if(i == 0 || i == 2) {
            res = pthread_create(&film[i],0,objor,&i);
            if(res) {
                printf("(!) Filosof (objora) %d ne priwel\n\n", i + 1);
                return EXIT_FAILURE;
            }
            else printf("Filosof (objora) %d prishel na obed\n\n", i + 1);
            sem_wait(&sem);
        }
        else {
            res = pthread_create(&film[i],0,fil,&i);
            if(res) {
                printf("(!) Filosof %d ne priwel\n\n", i + 1);
                return EXIT_FAILURE;
            }
            else printf("Filosof %d prishel na obed\n\n", i + 1);
            sem_wait(&sem);
        }

    }
    sem_wait(&podmig);

    res = pthread_join(film[1],NULL);
    if(res) return EXIT_FAILURE;

    sem_destroy(&sem);
    for(i = 0; i < N; i++) pthread_mutex_destroy(vilka);
    printf("Done\n");
    return EXIT_SUCCESS;
}

void *fil(void *arg) {

    int loc_id = *(int *)arg;
    int res1,res2;
    sem_post(&sem);
    while(1){
        if(golod[loc_id] > 10) {
            printf("Filosof %i umer ot goloda\n\n", loc_id + 1);
            break;
        }
        res1 = pthread_mutex_trylock(&vilka[loc_id%N]);
        res2 = pthread_mutex_trylock(&vilka[(loc_id + 1)%N]);
        if(res1 || res2) {
            golod[loc_id]++;
            if(res1 && res2) {
                printf("Filosof % i ne smog vzat ni odnoy vilki\n\n", loc_id + 1);
            }
            else if(res1 && !res2) {
                printf("Filosof %i ne smog vzat levuu vilku i otdal ee\n\n", loc_id + 1);
                pthread_mutex_unlock(&vilka[(loc_id + 1)%N]);
            }
            else if(!res1 && res2) {
                printf("Filosof %i ne smog vzat pravuu vilku i otdal ee\n\n", loc_id + 1);
                pthread_mutex_unlock(&vilka[loc_id%N]);
            }
            printf("Filosof %i golodaet %d raz\n\n", loc_id + 1,  golod[loc_id]);
            sleep(3);
        }
        else {
            golod[loc_id] = 0;
            printf("Filosof %i kushaet\n\n", loc_id);
            sleep(1);
            pthread_mutex_unlock(&vilka[loc_id%N]);
            printf("Filosof %i polojil levuu vilku\n\n", loc_id + 1);
            pthread_mutex_unlock(&vilka[(loc_id+1)%N]);
            printf("Filosof %i polojil pravuu vilku\n\n", loc_id + 1);
            sleep(3);
        }

    }
    return NULL;
}

void *objor(void *arg) {
    int loc_id = *(int *)arg;
    sem_post(&sem);
    while(1){
        pthread_mutex_lock(&vilka[(loc_id+1)%N]);
        printf("Filosof %i (objora) vzal pravuu vilku\n\n", loc_id + 1);
        pthread_mutex_lock(&vilka[loc_id%N]);
        printf("Filosof %i (objora) vzal levuu vilku\n\n", loc_id + 1);
        sem_post(&podmig);
        printf("Filosof %i (objora) kushaet\n\n", loc_id + 1);
        sleep(3);
        printf("Filosof %i (objora) poel i jdet signala polojit vilki\n\n", loc_id + 1);
        sem_wait(&podmig);
        pthread_mutex_unlock(&vilka[(loc_id+1)%N]);
        printf("Filosof %i (objora) polojil pravuu vilku\n\n", loc_id + 1);
        pthread_mutex_unlock(&vilka[loc_id%N]);
        printf("Filosof %i (objora) polojil levuu vilku\n\n", loc_id + 1);
        sleep(2);
    }
    return NULL;
}
