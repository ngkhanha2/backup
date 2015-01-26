/*
 * main.c
 *
 *  Created on: Dec 6, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int *S, int lower, int upper, int pos) {
	int pivot = S[pos];
	swap(&S[lower], &S[pos]);
	pos = lower;
	int i;
	for (i = lower + 1; i <= upper; ++i) {
		if (pivot > S[i]) {
			++pos;
			swap(&S[i], &S[pos]);
		}
	}
	swap(&S[lower], &S[pos]);
	return pos;
}

int selection(int *S, int lower, int upper, int k) {
	int index = lower + rand() % (upper - lower + 1);
	int pos = partition(S, lower, upper, index);
	if (pos == k) {
		return S[pos];
	}
	if (pos > k) {
		return selection(S, lower, pos - 1, k);
	}
	return selection(S, pos + 1, upper, k);
}

void input(int **S, int *n, int *k) {
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d %d", n, k);
	*S = (int *) calloc(*n, sizeof(int));
	int i;
	for (i = 0; i < *n; ++i) {
		fscanf(fi, "%d", &(*S)[i]);
	}
	fclose(fi);
}

int main() {
	int n, k;
	int *S = NULL;
	input(&S, &n, &k);
	--n;
	--k;
	FILE *fo = fopen(FILE_OUT, "wt");
	fprintf(fo, "%d", selection(S, 0, n, k));
	fclose(fo);
	free(S);
	return 0;
}
