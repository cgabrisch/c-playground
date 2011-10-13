#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>
#include "primes.h"
#include <signal.h>

static void * shmaddr;

void detach(int signal) {
    if (shmdt(shmaddr)) {
	printf("shmdt failed with errno %d\n", errno);
    } else {
	printf("Successfully detached from shared memory\n");
    }
}

int main(void) {
    struct sigaction sigaction_def;
    sigaction_def.sa_handler = detach;
    sigaction_def.sa_flags = SA_ONESHOT;
    sigaction(SIGTERM, &sigaction_def, NULL);

    key_t key = 76;
    size_t shmsize = 2 * sizeof(long);
    int shmid = shmget(key, shmsize, 0);
    if (shmid == -1) {
	printf("shmget failed with errno %d\n", errno);
	return -1;
    }

    shmaddr = shmat(shmid, NULL, SHM_RDONLY);
    if (shmaddr == (void *) -1) {
	printf("shmat failed with errno %d\n", errno);
	return -1;
    }

    long * current_candidate = (long *) shmaddr;
    long * last_prime = current_candidate++;

    prime_searcher_observer(50000, current_candidate, last_prime);

    return 0;
}


