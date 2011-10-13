#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "primes.h"

static long * current_candidate;
static long * last_prime;

void * prime_searcher_observer_wrapper(void * arg) {
    int * sleep_time = (int *) arg;
    prime_searcher_observer(*sleep_time, current_candidate, last_prime);

    return NULL;
}

void * prime_searcher_wrapper(void * arg) {
    prime_searcher(current_candidate, last_prime);
    return NULL;
}


int main(int argc, char ** args) {
    if (argc != 2) {
	fprintf(stderr, "Usage: %s <sleeptime observing thread>\n", *args);
	exit(1);
    }

    current_candidate = (long *) malloc(sizeof(long));
    last_prime = (long *) malloc(sizeof(long));

    pthread_t thread1;
    pthread_t thread2;
    
    if (pthread_create(&thread1, NULL, prime_searcher_wrapper, NULL)) {
	printf("Error");
	exit(1);
    }

    int sleep_time;
    sscanf(*++args, "%d", &sleep_time);

    if (pthread_create(&thread2, NULL, prime_searcher_observer_wrapper, &sleep_time)) {
	printf("Error");
	exit(1);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    free(current_candidate);
    free(last_prime);

    return 0;
}
