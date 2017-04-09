#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int findPrimes(int n, int t);

int main(int argc, char **argv) {
	int n = atoi(argv[1]);
	int t = atoi(argv[2]);
	findPrimes(n, t);
	return 0;
}

int findPrimes(int n, int t) 
{
	double tstart = 0.0, ttaken;
	char filename[32];
	sprintf(filename, "%d.txt", n);
	FILE *f = fopen(filename, "w");
	int i = 0;
	int j = 0;
	int *nums = (int *)calloc(n, sizeof(int)); 
	// calloc ensures initial values are 0
	// 0 will indicate prime
	// how small of an array can I malloc?
	nums[0] = 1; // 0 and 1 are not prime
	nums[1] = 1;
	int stop1 = (n + 1) / 2;
	int stop2 = 0;
	tstart = omp_get_wtime();
#	pragma omp parallel for num_threads(t) private(i, j, stop2) shared(nums, stop1)
	for (j = 2; j < stop1; j++) {
		// n = 10
		// j = 2, i = 2 --> 4
		// j = 2, i = 3 --> 6
		// j = 2, i = 4 --> 8
		// j = 2, i = 5 --> 10
		// j = 3, i = 2 --> 6
		// j = 3, i = 3 --> 9
		// j = 3, i = 4 --> 12 > 10 XX
		// j = 4, i = 2 --> 8
		// j = 5, i = 3 --> 15 > 10 XX
		stop2 = n / j + 1;
		for (i = 2; i < stop2; i++) {
			nums[(j * i)] = 1;
		}
	}
	ttaken = omp_get_wtime() - tstart;
	printf("Time taken for the main part: %f\n", ttaken);
	int prev = 2;
	int count = 1;
	for (j = 2; j < n; j++) {
		if (nums[j] == 0) {
			fprintf(f, "%d, %d, %d\n", count, j, j - prev);
			prev = j;
			count++;
		}
	}

	return 0;
}