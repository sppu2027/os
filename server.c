// SERVER PROGRAM
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    // Generate unique key
    key_t key = ftok("shmfile", 65);

    // Create shared memory segment
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach to shared memory
    char *str = (char*) shmat(shmid, NULL, 0);

    printf("Write Data: ");
    fgets(str, 1024, stdin);  // read from keyboard

    printf("Data written in memory: %s\n", str);

    // Detach from shared memory
    shmdt(str);

    return 0;
}
