#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}

void sstf(int req[], int n, int head) {
    int completed[n], count = 0, total = 0, i, index;
    for (i = 0; i < n; i++) completed[i] = 0;
    printf("\nSSTF Order: %d", head);
    while (count < n) {
        int min = 9999;
        for (i = 0; i < n; i++) {
            if (!completed[i] && abs(head - req[i]) < min) {
                min = abs(head - req[i]);
                index = i;
            }
        }
        total += abs(head - req[index]);
        head = req[index];
        completed[index] = 1;
        printf(" -> %d", head);
        count++;
    }
    printf("\nTotal Head Movement = %d\n", total);
}

void scan(int req[], int n, int head, int disk_size) {
    sort(req, n);
    int total = 0, i, pos = 0;

    // find position of head
    for (i = 0; i < n; i++)
        if (req[i] > head) { pos = i; break; }

    printf("\nSCAN Order: %d", head);
    // move towards higher tracks (away from spindle)
    for (i = pos; i < n; i++) {
        total += abs(head - req[i]);
        head = req[i];
        printf(" -> %d", head);
    }
    // go to end (disk_size-1)
    total += abs((disk_size - 1) - head);
    head = disk_size - 1;
    // now go back
    for (i = pos - 1; i >= 0; i--) {
        total += abs(head - req[i]);
        head = req[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Head Movement = %d\n", total);
}

void clook(int req[], int n, int head) {
    sort(req, n);
    int total = 0, i, pos = 0;

    for (i = 0; i < n; i++)
        if (req[i] > head) { pos = i; break; }

    printf("\nC-LOOK Order: %d", head);
    // move towards higher requests
    for (i = pos; i < n; i++) {
        total += abs(head - req[i]);
        head = req[i];
        printf(" -> %d", head);
    }
    // jump back to lowest request
    total += abs(head - req[0]);
    head = req[0];
    // continue till the one before 'pos'
    for (i = 1; i < pos; i++) {
        total += abs(head - req[i]);
        head = req[i];
        printf(" -> %d", head);
    }
    printf("\nTotal Head Movement = %d\n", total);
}

int main() {
    int n, head, disk_size, i;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int req[n];
    printf("Enter request sequence:\n");
    for (i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);

    sstf(req, n, head);
    scan(req, n, head, disk_size);
    clook(req, n, head);

    return 0;
}
