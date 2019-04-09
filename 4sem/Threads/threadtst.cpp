#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/times.h>

// Thread body function
void* run(void* arg);

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
        // PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

int main() {
    pthread_t thread1, thread2;
    int num1 = 1;
    int num2 = 2;

    srand(times(NULL)); // Set the random generator

    // Create the first thread
    int res = pthread_create(
        &thread1,   // Thread identifier
        NULL,       // Thread attributes: using defaults
        &run,       // Thread start function
        &num1       // Parameter to be passed to thread function
    );
    if (res != 0) {
        perror("Cannot create thread 1");
        exit(1);
    }
    pthread_mutex_lock(&mutex);
    printf("Thread 1 is created.\n");
    pthread_mutex_unlock(&mutex);

    // Create the second thread
    res = pthread_create(&thread2, NULL, &run, &num2);
    if (res != 0) {
        perror("Cannot create thread 2");
        exit(1);
    }
    pthread_mutex_lock(&mutex);
    printf("Thread 2 is created.\n");
    pthread_mutex_unlock(&mutex);

    // Wait until threads terminate
    pthread_join(
        thread1, // Thread ID
        NULL     // Location to store the return value of thread: not used
    );
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

void* run(void* arg) {
    int i;
    int num = *((int *) arg);

    for (i = 0; i < 10; i++) {
        int r = rand();
        r %= 3;

        pthread_mutex_lock(&mutex);
        printf("Thread %d.\n", num);
        pthread_mutex_unlock(&mutex);

        sched_yield();  // Give time to other threads
        sleep(r);       // Sleep does the same...
    }
    return NULL;
}
