#include <stdio.h>
int main() {
	int n, m, i, j, k;
	printf("Enter number of processes: ");
	scanf("%d", &n);
	printf("Enter number of resource types: ");
	scanf("%d", &m);
	int Allocation[n][m], Max[n][m], Need[n][m], Available[m], Finish[n], SafeSeq[n];
	printf("Enter Allocation Matrix:\n");
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			scanf("%d",&Allocation[i][j]);
		}
	}
// Input Max Matrix
	printf("Enter Maximum Matrix:\n");
	for(i=0; i<n; i++) {
		for(j=0; j<m; j++) {
			scanf("%d",&Max[i][j]);
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}
	printf("Enter Available Resources: ");
	for(j=0; j<m; j++)
		scanf("%d",&Available[j]);
	for(i=0; i<n; i++)
		Finish[i] = 0;
	int count = 0;
	while(count < n) {
		int found = 0;
		for(i=0; i<n; i++) {
			if(Finish[i]==0) {
				int flag = 1;
				for(j=0; j<m; j++) {
					if(Need[i][j] > Available[j]) {
						flag = 0;
						break;
					}
				}
				if(flag) {
				// Process can be executed
					for(k=0; k<m; k++)
						Available[k] += Allocation[i][k];
					SafeSeq[count] = i;
					count++;
					Finish[i] = 1;
					found = 1;
				}
			}
		}
		if(!found) {
			printf("\nSystem is in Unsafe State! Deadlock may occur.\n");
			return 0;
		}
	}
	printf("\nSystem is in Safe State.\nSafe Sequence is: ");
	for(i=0; i<n; i++) {
		printf("P%d", SafeSeq[i]);
		if(i != n-1) printf(" -> ");
	}
	printf("\n");
	return 0;
}