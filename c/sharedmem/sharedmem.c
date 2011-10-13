#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "primes.h"
#include <errno.h>
#include <stdio.h>

int main(void) {
    key_t key = 76;
    size_t shmsize = 2 * sizeof(long);
    int shmid = shmget(key, shmsize, IPC_EXCL | IPC_CREAT | 0700);
    if (shmid == -1) {
	printf("shmget failed with errno %d\n", errno);
	return -1;
    }

    void * shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void *) -1) {
	printf("shmat failed with errno %d\n", errno);
	return -1;
    }

    long * current_candidate = (long *) shmaddr;
    long * last_prime = current_candidate++;

    prime_searcher(current_candidate, last_prime);

    return 0;
}
