#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include "primes.h"

void prime_searcher_observer(int sleep_time, long* current_candidate, long* last_prime) {
    while (1) {
	printf("Current candidate: %ld Last prime: %ld\n", *current_candidate, *last_prime);
	usleep(sleep_time);
    }
}

static int is_prime(long);

void prime_searcher(long* current_candidate, long* last_prime) {
    for (*current_candidate = 2; *current_candidate < LONG_MAX; (*current_candidate)++) {
	if (is_prime(*current_candidate)) {
	    *last_prime = *current_candidate;
	}
    }
}

static int is_prime(long candidate) {
    long i = 2;
    for (i = 2; i < candidate; i++) {
	if (candidate % i == 0) {
	    return 0;
	}
    }

    return 1;
}
