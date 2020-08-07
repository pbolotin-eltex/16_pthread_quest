#include <pthread.h>
#include <stdio.h>

#define THREADS_COUNT 1000
#define CYCLE_LIMIT 1000000

/* Threads will use this function 
 * its just prototype.
 * See below full definition please. */
void* func(void* par);

/* The only one variable where different
 * threads will fight for the right to read and write.
 * each of them will be trying to change value with using buffer
 * but it is not "atomic" operation, and has side effects. */
int A = 0;

/* This is array of variables where each thread can read and write on
 * its own place. */
int AR[THREADS_COUNT];

/* This is array of parameters, only one of them
 * each thread will take */
int param[THREADS_COUNT];

int main() {
    /* Variable for threads ids */
    pthread_t tid[THREADS_COUNT];
    int i;
    
    /* Main thread starts threads 
     * giving each of them address
     * in the global AR array where they can write */
    for(i = 0; i < THREADS_COUNT; i++) {
        param[i] = i;
        pthread_create(&tid[i], NULL, func, (&param[i]));
    }
    /* Here main thread wait for the ending of other threads */
    for(i = 0; i < THREADS_COUNT; i++) {
        pthread_join(tid[i], NULL);
    }
    /* And will print result of unsafety method of shared using of the
     * variable A */
    printf("Result: %d\n", A);
    
    
    /* Now main thread will calculate sum through the AR array
     * and print it. It will be defined number other than that above */
    A = 0;
    for(int i = 0; i < THREADS_COUNT; i++) {
        A += AR[i];
    }
    printf("Result: %d\n", A);
    return 0;
}

void* func(void* par) {
    int tmp;
    int i;
    for(i = 0; i < CYCLE_LIMIT; i++) {
        /* Part one, value A have risk to be undefined in the end.
         * Threads can read A at the same time, when A have the same
         * value for different of them because of each of them can
         * be stopped by task manager, on half performing sequence
         * of cycle operations, not completed yet. */
        tmp = A;
        tmp++;
        A = tmp;
        /* This is more safety way, but for each thread it has the only 
         * one place to reading and writing. */
        AR[*((int*)par)]++;
    }
    /* Each thread before its end show its number that had been taken
     * from main thread as parameter */
    printf("func %d\n", *((int*)par));
    pthread_exit(0);
    return (void*)0;
}
