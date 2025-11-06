// CLIENT PROGRAM
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    // Generate the same key
    key_t key = ftok("shmfile", 65);

    // Locate shared memory segment
    int shmid = shmget(key, 1024, 0666);

    // Attach to shared memory
    char *str = (char*) shmat(shmid, NULL, 0);

    printf("Data read from memory: %s\n", str);

    // Detach from shared memory
    shmdt(str);

    // Destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
