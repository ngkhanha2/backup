/*
 * main.c
 *
 *  Created on: Nov 13, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

void print(FILE *fo, int *r, int n) {
	int i;
	fprintf(fo, "{%d", r[0]);
	for (i = 1; i < n; ++i) {
		fprintf(fo, "; %d", r[i]);
	}
	fprintf(fo, "}\n");
}

void sumOfubsets(FILE *fo, int *val, int *r, int k, int start, int sum,
		int total, int n, int W) {
	int i, lost = 0;
	if (sum == W) {
		print(fo, r, k);
	} else {
		for (i = start; i < n; ++i) {
			if (sum + total - lost >= W && sum + val[i] <= W) {
				r[k] = val[i];
				sumOfubsets(fo, val, r, k + 1, i + 1, sum + val[i],
						total - val[i] - lost, n, W);
			}
			lost += val[i];
		}
	}
}

void input(int **val, int *total, int *n, int *W) {
	int i;
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d %d", n, W);
	*val = (int*) calloc(*n, sizeof(int));
	*total = 0;
	for (i = 0; i < *n; ++i) {
		fscanf(fi, "%d", &(*val)[i]);
		*total += (*val)[i];
	}
	fclose(fi);
}

int compare(const void *a, const void *b) {
	return *(int*) a - *(int*) b;
}

int main() {
	int n, W, total;
	int *val = NULL;
	int *r = NULL;
	input(&val, &total, &n, &W);
	r = (int*) calloc(n, sizeof(int));
	memset(r, 0, sizeof(int) * n);
	FILE *fo = fopen(FILE_OUT, "wt");
	qsort(val, n, sizeof(int), compare);
	if (val[0] <= W && W <= total) {
		sumOfubsets(fo, val, r, 0, 0, 0, total, n, W);
	}
	fclose(fo);
	free(val);
	free(r);
	return 0;
}
