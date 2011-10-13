#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    if (argc != 2) {
	printf("Usage: shmremove <shmkey>\n");
	return 1;
    }

    key_t shmkey = atoi(*(argv+1));
    
    printf("shmkey=%d\n", shmkey);
    
    int shmid = shmget(shmkey, 0, 0);
    if (shmid == -1) {
	printf("shmget failed with errno %d\n", errno);
	return -1;
    }

    struct shmid_ds shmid_ds;
    if (shmctl(shmid, IPC_STAT, &shmid_ds) < 0) {
	printf("shmctl IPC_STAT failed with errno %d\n", errno);
	return -1;
    }

    if (shmctl(shmid, IPC_RMID, &shmid_ds) < 0) {
	printf("shmctl IPC_RMID failed with errno %d\n", errno);
	return -1;
    }

    return 0;
}
