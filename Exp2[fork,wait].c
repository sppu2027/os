#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function for bubble sort
void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


int main() {
    int n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    pid_t pid = fork();  // Create new process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child Process
        printf("\n[CHILD] Process ID: %d, Parent ID: %d\n", getpid(), getppid());
        printf("[CHILD] Performing Sort...\n");
        bubbleSort(arr, n);
        printf("[CHILD] Sorted Array: ");
        for(int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        // To demonstrate Orphan state
        sleep(10);
        printf("[CHILD] After 10 sec (Orphan demo) - My new Parent ID: %d\n", getppid());
        exit(0);
    }
    else {
        // Parent Process
        printf("\n[PARENT] Process ID: %d, Child ID: %d\n", getpid(), pid);
        printf("[PARENT] Performing Sort...\n");
        bubbleSort(arr, n);
        printf("[PARENT] Sorted Array: ");
        for(int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        // To demonstrate Zombie state
        printf("[PARENT] Sleeping for 10 seconds to create Zombie...\n");
        sleep(10);  // Child finishes, but parent hasn't waited yet
        printf("[PARENT] Now calling wait() to remove Zombie state...\n");

        wait(NULL);
        printf("[PARENT] Child process finished. Exiting...\n");
    }

    return 0;
}
