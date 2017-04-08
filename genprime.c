#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <omp.h>

int findPrimes(int n, int t);

int main(int argc, char **argv) {
	int n = atoi(argv[1]);
	int t = atoi(argv[2]);
	findPrimes(n, t);
	return 0;
}

int findPrimes(int n, int t) {
	int i;
	int j;
	int *nums = (int *)calloc(n, sizeof(int)); 
	// calloc ensures initial values are 0
	// 0 will indicate prime
	// how small of an array can I malloc?
	nums[0] = 1; // 0 and 1 are not prime
	nums[1] = 1;
	int stop = floor((n + 1) / 2);
	for (j = 2; j < stop; j++) {
		for (i = j + 1; i < n; i++) {
			if (i % j == 0) {
				nums[i] = 1; // all multiples of j are not prime
			}
		}
	}
	int prev = 2;
	int count = 1;
	for (j = 2; j < n; j++) {
		if (nums[j] == 0) {
			printf("%d, %d, %d\n", count, j, j - prev);
			prev = j;
			count++;
		}
	}

	return 0;
}