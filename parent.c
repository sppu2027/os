#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Bubble sort function
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
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();  // create child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("\n[CHILD] Created. Executing new program using execve()...\n");

        // Prepare arguments for execve
        char *args[n + 2]; // n elements + program name + NULL terminator
        args[0] = "./child"; // program to execute

        for (int i = 0; i < n; i++) {
            char *numStr = (char *)malloc(10);
            sprintf(numStr, "%d", arr[i]);
            args[i + 1] = numStr;
        }
        args[n + 1] = NULL; // Null terminate argument list

        // Execute child program
        execve(args[0], args, NULL);

        // If execve fails
        perror("execve failed");
        exit(1);
    } 
    else {
        // Parent process
        printf("\n[PARENT] Sorting array using Bubble Sort...\n");
        bubbleSort(arr, n);

        printf("[PARENT] Sorted array: ");
        for(int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");

        // Wait for child to finish
        wait(NULL);
        printf("[PARENT] Child process completed.\n");
    }

    return 0;
}
